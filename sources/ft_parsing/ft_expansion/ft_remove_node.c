/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:18:48 by tlassere          #+#    #+#             */
/*   Updated: 2025/05/11 15:46:14 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_del_node(t_data *data, t_list **lst, t_list *last, t_list *next)
{
	if (((t_word *)(*lst)->content)->word == NULL)
	{
		ft_word_free((*lst)->content);
		free(*lst);
		*lst = next;
		if (last)
			last->next = next;
		else
			data->words = next;
	}
}

void	ft_while_del_node(t_data *data)
{
	t_list	*next;
	t_list	*prev;
	t_list	*current;

	current = data->words;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (((t_word *)current->content)->type == D_NOT_SET)
			ft_del_node(data, &current, prev, next);
		if (current != next)
		{
			prev = current;
			current = next;
		}
	}
}
