/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:51:45 by tlassere          #+#    #+#             */
/*   Updated: 2024/01/31 21:48:09 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_tab_make(const char **tab)
{
	char	**new_tab;
	int		len;

	len = ft_tab_len((char **)tab);
	new_tab = malloc((len + 2) * sizeof(char **));
	if (new_tab)
		new_tab[len + 1] = NULL;
	return (new_tab);
}

static int	ft_tab_insert(char **new_tab, const char **old_tab, const char *el)
{
	int				ret;
	unsigned int	i;

	ret = 0;
	i = 0;
	while (new_tab[i] && ret != MALLOC_FAIL)
	{
		if (new_tab[i + 1])
			new_tab[i] = ft_strdup(old_tab[i]);
		else
			new_tab[i] = ft_strdup(el);
		if (new_tab[i] == NULL)
			ret = MALLOC_FAIL;
		i++;
	}
	if (ret == MALLOC_FAIL)
		ft_tab_free(new_tab);
	return (ret);
}

char	**ft_tab_join(const char **tab, const char *el)
{
	char	**new_tab;

	new_tab = NULL;
	if (tab && el)
	{
		new_tab = ft_tab_make(tab);
		if (new_tab && ft_tab_insert(new_tab, tab, el) == MALLOC_FAIL)
			new_tab = NULL;
	}
	return (new_tab);
}
