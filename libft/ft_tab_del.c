/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:43:00 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/01 21:26:03 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tab_del(char **tab, int index)
{
	char	**new_tab;
	int		len;

	new_tab = tab;
	if (tab)
	{
		len = ft_tab_len(tab);
		if (index >= 0 && index < len)
		{
			new_tab = malloc(sizeof(char **) * len);
			if (new_tab)
			{
				ft_memmove(new_tab, tab, sizeof(char **) * index);
				ft_memmove(new_tab + index, tab + index + 1,
					sizeof(char **) * (len - index));
				free(*(tab + index));
				free(tab);
			}
		}
	}
	return (new_tab);
}
