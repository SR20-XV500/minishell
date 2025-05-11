/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:21:32 by tlassere          #+#    #+#             */
/*   Updated: 2025/05/11 17:05:25 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_redirect_get_path_parser(t_data *data, const char *path)
{
	char	*path_created;

	path_created = NULL;
	if (path)
	{
		if (*path == '\0' || ft_strncmp(path, "/", 1) == CMP_EGAL)
			path_created = ft_strdup(path);
		else
			path_created = ft_path_parser(data->env->pwd, path);
	}
	return (path_created);
}

static void	ft_redirect_display_error(t_data *data, const char *error,
		char **path, int status)
{
	data->env->exit_status = REDIRECT_FAIL;
	if (*path && **path == '\0')
	{
		ft_fprintf(STDERR, ERR_SUCH_FILE, "");
		free(*path);
		*path = NULL;
	}
	else if (status == REDIRECT_AMBIGUOUS_REDIRECT)
		ft_fprintf(STDERR, ERR_AMBIGUOUS_REDIRECT, error);
}

char	*ft_redirect_get_path(t_data *data, t_word *word, char *error)
{
	char	*path;

	path = NULL;
	if (word)
		path = ft_redirect_get_path_parser(data, word->word);
	else
		ft_redirect_display_error(data, error,
			&path, REDIRECT_AMBIGUOUS_REDIRECT);
	if (path && path[0] == '\0')
		ft_redirect_display_error(data, NULL, &path, 0);
	return (path);
}
