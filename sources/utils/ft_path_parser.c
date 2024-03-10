/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 22:23:16 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/09 16:48:08 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_path_word(char ***pwd, const char *word)
{
	char	**buffer_tab;
	int		exit_status;

	exit_status = MALLOC_FAIL;
	buffer_tab = ft_tab_join(*pwd, word);
	if (buffer_tab)
	{
		exit_status = SUCCESS;
		*pwd = buffer_tab;
	}
	return (exit_status);
}

int	ft_path_down(char ***pwd)
{
	char	**buffer;
	int		exit_status;

	exit_status = MALLOC_FAIL;
	if (**pwd)
		buffer = ft_tab_del(*pwd, ft_tab_len(*pwd) - 1);
	else
		buffer = *pwd;
	if (buffer)
	{
		exit_status = SUCCESS;
		*pwd = buffer;
	}
	return (exit_status);
}

static char	*ft_path_update(char ***pwd, char **change_dir)
{
	char		*new_path;
	int			status;

	status = SUCCESS;
	new_path = NULL;
	while (*change_dir && status != MALLOC_FAIL)
	{
		if (ft_strncmp(*change_dir, "..", 3) == CMP_EGAL)
			status = ft_path_down(pwd);
		else if (ft_strncmp(*change_dir, ".", 2) != CMP_EGAL)
			status = ft_path_word(pwd, *change_dir);
		change_dir++;
	}
	if (status == SUCCESS)
		new_path = ft_path_tab_to_str(*pwd);
	if (new_path)
	{
		ft_memmove(new_path + 1, new_path, ft_strlen(new_path) - 1);
		new_path[0] = '/';
	}
	return (new_path);
}

char	*ft_path_parser(const char *path, const char *change_path)
{
	char	*new_path;
	char	**split_change_path;
	char	**split_path;

	new_path = NULL;
	split_change_path = NULL;
	split_path = NULL;
	if (path && change_path)
	{
		split_path = ft_split(path, '/');
		split_change_path = ft_split(change_path, '/');
		if (split_path && split_change_path)
			new_path = ft_path_update(&split_path, split_change_path);
		if (split_change_path)
			ft_tab_free(split_change_path);
		if (split_path)
			ft_tab_free(split_path);
	}
	return (new_path);
}
