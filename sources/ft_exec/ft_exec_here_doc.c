/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:35:33 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/27 18:29:54 by tlassere         ###   ########.fr       */
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

int	ft_count_here_doc(t_data *data)
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
