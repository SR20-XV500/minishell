/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:38:02 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/06 00:36:15 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_path_tab_resort(char *start,
	const char *dest, int (*f)(const char *))
{
	char	*path;
	char	*buffer_path;

	path = NULL;
	if (start && dest && f)
	{
		buffer_path = ft_path_parser(start, dest);
		if (buffer_path)
		{
			if ((*f)(buffer_path) == SUCCESS)
				path = buffer_path;
			else
				free(buffer_path);
		}
	}
	return (path);
}

static char	*ft_path_resort(const char *path, const char *dest, t_env *env,
	int (*f)(const char *))
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
		while (tab && tab[i] && path_valid == NULL)
		{
			sub_path = tab[i];
			if (tab[i][0] != '/')
				sub_path = ft_path_parser(env->pwd, sub_path);
			path_valid = ft_path_tab_resort(sub_path, dest, f);
			if (sub_path && sub_path != tab[i])
				free(sub_path);
			i++;
		}
		ft_tab_free(tab);
	}
	return (path_valid);
}

char	*ft_path_multiple_file(const char *multie_path, const char *dest,
	t_env *env)
{
	return (ft_path_resort(multie_path, dest, env, &ft_is_file));
}
