/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_dump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:06:48 by tlassere          #+#    #+#             */
/*   Updated: 2024/01/30 18:32:55 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tab_dump(char **tab)
{
	char	**new_tab;
	int		tab_size;

	if (tab == NULL)
		return (NULL);
	tab_size = ft_tab_len(tab);
	new_tab = malloc((tab_size + 1) * sizeof(char **));
	if (new_tab == NULL)
		return (NULL);
	new_tab[tab_size] = NULL;
	tab_size = 0;
	while (tab[tab_size])
	{
		new_tab[tab_size] = ft_strdup(tab[tab_size]);
		if (new_tab[tab_size] == NULL)
			return (ft_tab_free(new_tab), NULL);
		tab_size++;
	}
	return (new_tab);
}
