/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:54:04 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/01 20:15:02 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_tab_set(char *str, char **tab)
{
	char	**new_tab;
	int		len;

	len = ft_tab_len(tab);
	new_tab = malloc(sizeof(char **) * (len + 2));
	if (new_tab)
	{
		ft_memmove(new_tab, tab, sizeof(char **) * len);
		new_tab[len] = str;
		new_tab[len + 1] = NULL;
	}
	return (new_tab);
}

char	**ft_tab_join(char **tab, const char *el)
{
	char	**new_tab;
	char	*new_str;

	new_tab = NULL;
	if (tab && el)
	{
		new_str = ft_strdup(el);
		if (new_str)
		{
			new_tab = ft_tab_set(new_str, tab);
			if (new_tab)
				free(tab);
			else
				free(new_str);
		}
	}
	return (new_tab);
}
