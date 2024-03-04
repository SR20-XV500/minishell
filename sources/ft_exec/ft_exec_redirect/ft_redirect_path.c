/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:21:32 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/04 18:50:36 by tlassere         ###   ########.fr       */
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

static void	ft_redirect_display_error(t_data *data, const char *error,
		char **path, int status)
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

char	*ft_trim_ambiguous(char *str)
{
	size_t	index;
	int		buffer;

	index = 0;
	buffer = SUCCESS;
	if (str)
	{
		while (str[index] && ft_strchr(" \t\v\f\r\n", str[index]))
			index++;
		ft_memmove(str, str + index, ft_strlen(str + index) + 1);
		index = ft_strlen(str);
		while (ft_strchr(" \t\v\f\r\n", str[index]) && buffer == SUCCESS)
		{
			str[index] = '\0';
			if (index == 0)
				buffer = FAIL;
			else
				index--;
		}
	}
	return (str);
}

char	*ft_redirect_get_path(t_data *data, const char *str)
{
	char	*path;
	char	*buff;
	int		status;

	path = NULL;
	buff = NULL;
	status = REDIRECT_AMBIGUOUS_REDIRECT;
	if (str)
	{
		buff = ft_trim_ambiguous(ft_expansion_get_str(data, str));
		if (buff && ft_expansion_is_multi_arg(buff) == FAIL && *buff)
		{
			status = MALLOC_FAIL;
			ft_quotes_remove(buff);
			path = ft_redirect_get_path_parser(data, buff);
			if (path)
				status = SUCCESS;
		}
	}
	if (buff && status != REDIRECT_AMBIGUOUS_REDIRECT)
		ft_redirect_display_error(data, buff, &path, status);
	else
		ft_redirect_display_error(data, str, &path, status);
	free(buff);
	return (path);
}
