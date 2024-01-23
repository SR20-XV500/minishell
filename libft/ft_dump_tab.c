/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dump_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:06:48 by tlassere          #+#    #+#             */
/*   Updated: 2023/11/23 19:41:39 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dump_tab(char **tab)
{
	char	**new_tab;
	int		tab_size;

	if (tab == NULL)
		return (NULL);
	tab_size = 0;
	while (tab[tab_size])
		tab_size++;
	new_tab = malloc((tab_size + 1) * sizeof(char **));
	if (new_tab == NULL)
		return (NULL);
	new_tab[tab_size] = NULL;
	tab_size = 0;
	while (tab[tab_size])
	{
		new_tab[tab_size] = ft_strdup(tab[tab_size]);
		if (new_tab[tab_size] == NULL)
			return (ft_free_tab(new_tab), NULL);
		tab_size++;
	}
	return (new_tab);
}
