/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 22:15:41 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/24 15:45:41 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*tmp;
	t_list	*n_lst;
	t_list	*buff;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	tmp = f(lst->content);
	if (!tmp)
		return (NULL);
	n_lst = ft_lstnew(tmp);
	if (n_lst == NULL)
		return (del(tmp), NULL);
	if (lst->next)
	{
		buff = ft_lstmap(lst->next, f, del);
		if (buff == NULL)
			return (ft_lstdelone(n_lst, del), NULL);
		n_lst->next = buff;
	}
	return (n_lst);
}
