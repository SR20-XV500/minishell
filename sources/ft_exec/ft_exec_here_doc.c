/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:35:33 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/27 19:16:39 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirect_priority(t_list *lst)
{
	int	priority;

	priority = NO_PRIORITY;
	while (lst && lst->content && ((t_word *)lst->content)->type != D_PIPE)
	{
		if (((t_word *)lst->content)->type == D_INPUT)
			priority = PRIORITY_INPUT;
		else if (((t_word *)lst->content)->type == D_HEREDOC)
			priority = PRIORITY_HERE_DOC;
		lst = lst->next;
	}
	return (priority);
}

static int	ft_count_here_doc(t_data *data)
{
	int		count;
	int		buffer;
	t_list	*lst;

	count = 0;
	buffer = SUCCESS;
	if (data)
	{
		lst = data->words;
		count++;
		while (lst && lst->content)
		{
			if (((t_word *)lst->content)->type == D_HEREDOC
				&& buffer == SUCCESS)
			{
				buffer = FAIL;
				count++;
			}
			else if (((t_word *)lst->content)->type == D_PIPE)
				buffer = SUCCESS;
			lst = lst->next;
		}
	}
	return (count);
}

static int	ft_make_here_doc(t_data *data)
{
	int	status;
	int	len;

	status = BAD_PARAMETER;
	if (data)
	{
		status = SUCCESS;
		len = ft_count_here_doc(data);
		if (len > 1)
		{
			data->here_doc = malloc(sizeof(t_list **) * len);
			if (data->here_doc)
				ft_bzero(data->here_doc, sizeof(t_list **) * len);
			else
				status = MALLOC_FAIL;
		}
	}
	return (status);
}

//int	ft_here_doc_add_content(t_data *data)
//{
//}

int	ft_exec_here_doc(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = ft_make_here_doc(data);
	}
	return (status);
}
