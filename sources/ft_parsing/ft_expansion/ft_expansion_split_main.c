/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_split_main.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:19:11 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/04 13:11:06 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_expansion_split_change_node(t_data *data, t_list *new_node,
	t_list *last, t_list **cur)
{
	t_list	*buffer_next;

	buffer_next = (*cur)->next;
	ft_word_free((*cur)->content);
	free(*cur);
	*cur = ft_lstlast(new_node);
	ft_lstadd_back(&new_node, buffer_next);
	if (last)
		last->next = new_node;
	else
		data->words = new_node;
}

int	ft_expansion_split_node(t_data *data, t_list **lst, t_list *last)
{
	int		status;
	t_list	*lst_split;

	status = BAD_PARAMETER;
	if (data && lst && *lst && (*lst)->content)
	{
		status = SUCCESS;
		if (ft_expansion_is_multi_arg(((t_word *)(*lst)->content)->word)
			== SUCCESS)
		{
			lst_split = ft_expansion_split_node_content(
					((t_word *)(*lst)->content)->word);
			if (lst_split)
				ft_expansion_split_change_node(data, lst_split, last, lst);
			else
				status = MALLOC_FAIL;
		}
	}
	(void)last;
	return (status);
}
