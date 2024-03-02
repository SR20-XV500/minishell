/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:21:32 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/27 15:19:59 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_redirect_get_path_parser(t_data *data, const char *path)
{
	char	*path_created;

	path_created = NULL;
	if (path)
	{
		if (ft_strncmp(path, "/", 1) == CMP_EGAL)
			path_created = ft_strdup(path);
		else
			path_created = ft_path_parser(data->env->pwd, path);
	}
	return (path_created);
}

static void	ft_redirect_display_error(t_data *data,
	const char *error, char **path, int status)
{
	if (status == REDIRECT_AMBIGUOUS_REDIRECT || (*path && **path == '\0'))
		data->env->exit_status = REDIRECT_FAIL;
	if (*path && **path == '\0')
	{
		ft_fprintf(STDERR, ERR_SUCH_FILE, *path);
		free(*path);
		*path = NULL;
	}
	else if (status == REDIRECT_AMBIGUOUS_REDIRECT)
		ft_fprintf(STDERR, ERR_AMBIGUOUS_REDIRECT, error);
}

char	*ft_redirect_get_path(t_data *data, const char *str)
{
	char	*path;
	char	*buffer;
	int		status;

	path = NULL;
	buffer = NULL;
	status = REDIRECT_AMBIGUOUS_REDIRECT;
	if (str)
	{
		buffer = ft_expansion_get_str(data, str);
		if (buffer && ft_expansion_is_multie_arg(buffer) == FAIL)
		{
			status = MALLOC_FAIL;
			ft_quotes_remove(buffer);
			path = ft_redirect_get_path_parser(data, buffer);
			if (path)
				status = SUCCESS;
		}
	}
	if (buffer && status != REDIRECT_AMBIGUOUS_REDIRECT)
		ft_redirect_display_error(data, buffer, &path, status);
	else
		ft_redirect_display_error(data, str, &path, status);
	free(buffer);
	return (path);
}
