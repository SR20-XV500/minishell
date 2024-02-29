/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:11:04 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/28 00:10:23 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_word_add_lst(t_list **lst_el, const char *str, int type)
{
	t_list	*lst;
	int		ret;

	ret = BAD_PARAMETER;
	if (lst_el)
	{
		ret = MALLOC_FAIL;
		lst = ft_word_lst_make(str, type);
		if (lst)
		{
			ret = SUCCESS;
			ft_lstadd_back(lst_el, lst);
		}
	}
	return (ret);
}
