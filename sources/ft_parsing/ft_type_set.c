/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:29:20 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/16 14:37:16 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_type_path(t_list *lst)
{
	t_list	*cur_lst;
	t_word	*cur_word;
	int		target;

	cur_lst = lst;
	cur_word = NULL;
	target = TY_NOT_SET;
	while (cur_lst)
	{
		cur_word = cur_lst->content;
		if (target != TY_NOT_SET)
		{
			cur_word->type = target;
			target = TY_NOT_SET;
		}
		else if (cur_word->type == D_INPUT || cur_word->type == D_OUTPUT_APPEND
			|| cur_word->type == D_OUTPUT_NEW)
			target = TY_PATH;
		else if (cur_word->type == D_HEREDOC)
			target = TY_DELIM_HEREDOC;
		cur_lst = cur_lst->next;
	}
}

static void	ft_type_cmd(t_list *lst)
{
	t_list	*cur_lst;
	t_word	*cur_word;
	int		target;

	cur_lst = lst;
	cur_word = NULL;
	target = TY_CMD;
	while (cur_lst)
	{
		cur_word = cur_lst->content;
		if (cur_word->type == D_NOT_SET)
		{
			cur_word->type = target;
			target = TY_ARG;
		}
		else if (cur_word->type == D_PIPE)
			target = TY_CMD;
		cur_lst = cur_lst->next;
	}
}

static int	ft_type_set(t_data *data, void (*f)(t_list *))
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = SUCCESS;
		(*f)(data->words);
	}
	return (status);
}

int	ft_type_set_path(t_data *data)
{
	return (ft_type_set(data, &ft_type_path));
}

int	ft_type_set_cmd(t_data *data)
{
	return (ft_type_set(data, &ft_type_cmd));
}
