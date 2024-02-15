/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_multie.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:38:02 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/15 14:33:45 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_path_tab_resort(char *start,
	const char *dest, (*f)(const char *))
{
	char	*path;
	char	*buffer_path;

	path = NULL;
	if (tab && dest && f)
	{
		buffer_path = ft_path_parser(start, dest);
		if ((*f)(buffer_path) == SUCCESS)
			path = buffer_path;
		else if (buffer_path)
			free(buffer_path);
	}
	return (path);
}

static char	*ft_path_resort(const char *path, const char *dest, (*f)(const char *))
{
	char	*path_valid;
	char	**tab;
	char	*sub_path;
	size_t	i;

	path_valid = NULL;
	tab = NULL;
	i = 0;
	if (path && dest && f)
	{
		tab = ft_split(path, ':');
		if (tab)
		{
			while (tab[i])
			{
				if (tab[i][0] != '/')
					
				path = ft_path_tab_resort(tab[i], dest f);
				i++;
			}
			ft_tab_free(tab);
		}
	}
	return (path_valid);
}

char	*ft_path_multiple_file(const char *multie_path, const char *dest)
{
	return (ft_path_resort(path, dest, &ft_is_file));
}
