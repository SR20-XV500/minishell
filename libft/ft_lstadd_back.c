/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:43:36 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/24 15:43:43 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*buff;

	if (lst == NULL || new == NULL)
		return ;
	buff = ft_lstlast(*lst);
	if (buff == NULL)
		ft_lstadd_front(lst, new);
	else
		buff->next = new;
}
