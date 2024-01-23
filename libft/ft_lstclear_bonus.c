/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:32:36 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/24 15:45:41 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*buff;
	t_list	*set;

	if (lst == NULL || *lst == NULL)
		return ;
	buff = *lst;
	while (buff->next)
	{
		set = buff->next;
		ft_lstdelone(buff, del);
		buff = set;
	}
	ft_lstdelone(buff, del);
	*lst = NULL;
}
