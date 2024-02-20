/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:38:06 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/20 02:20:02 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec_redirect_content(t_data *data, int type, t_word *word_path)
{
	int		status;
	char	*path;

	status = BAD_PARAMETER;
	path = NULL;
	if (data && type && word_path && word_path->word)
	{
		status = FAIL;
		path = ft_redirect_get_path(data, word_path->word);
		if (path)
		{
			status = ft_exec_redirect_fd(data, type, path, word_path->word);
			free(path);
		}
	}
	return (status);
}

static int	ft_exec_redirect(t_data *data, t_list *lst)
{
	int	status;
	int	type;

	status = BAD_PARAMETER;
	if (data && lst && lst->content)
	{
		status = SUCCESS;
		type = ((t_word *)lst->content)->type;
		if (type == D_INPUT || type == D_OUTPUT_APPEND || type == D_OUTPUT_NEW)
		{
			if (lst->next && lst->next->content
				&& ((t_word *)lst->next->content)->type == TY_PATH)
			{
				status = ft_exec_redirect_content(data, type,
						lst->next->content);
			}
			else
				status = FAIL;
		}
	}
	return (status);
}

static int	ft_exec_iter_lst(t_data *data)
{
	int		status;
	t_list	*lst;

	status = BAD_PARAMETER;
	if (data)
	{
		status = SUCCESS;
		lst = data->words;
		while (lst && status == SUCCESS)
		{
			status = ft_exec_redirect(data, lst);
			lst = lst->next;
		}
	}
	return (status);
}

int	ft_exec(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = ft_exec_iter_lst(data);
	}
	return (status);
}
