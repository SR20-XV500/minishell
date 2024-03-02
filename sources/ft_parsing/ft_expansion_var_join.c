/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_var_join.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:47:04 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/02 17:34:28 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_expansion_is_ambiguous(t_env *env, const char *name)
{
	int	status;

	status = FAIL;
	if (env)
	{
		if (ft_strncmp(name, "$?", 3) == CMP_EGAL)
			status = SUCCESS;
		else if (ft_strncmp(name, "$PATH", 6) == CMP_EGAL && env->path)
			status = SUCCESS;
	}
	return (status);
}

static int	ft_expansion_get_content_var(t_data *data,
	const char *name, char **content)
{
	int		status;
	char	*buffer;

	status = BAD_PARAMETER;
	buffer = NULL;
	if (name && content && *name)
	{
		status = SUCCESS;
		if (ft_env_get_pos(*(data->env), name + 1) != ENV_NOT_SET
			|| ft_expansion_is_ambiguous(data->env, name) == SUCCESS)
		{
			buffer = ft_env_get_content(*(data->env), name + 1);
			if (buffer == NULL)
				status = MALLOC_FAIL;
		}
		*content = buffer;
	}
	return (status);
}

static int	ft_expansion_get_content(t_data *data, const char *str,
	char **content, size_t *i)
{
	char	*name;
	int		status;
	size_t	sub;

	name = NULL;
	sub = 1;
	status = MALLOC_FAIL;
	if (str[sub] == '?')
		sub++;
	else
	{
		while (ft_isalnum(str[sub]) || str[sub] == '_')
			sub++;
	}
	name = ft_substr(str, 0, sub);
	if (name)
	{
		status = ft_expansion_get_content_var(data, name, content);
		free(name);
	}
	*i += sub - 1;
	return (status);
}

static int	ft_expansion_join(const char *str, char **buffer)
{
	int		status;
	char	*new_str;

	status = MALLOC_FAIL;
	new_str = ft_strjoin(*buffer, str);
	if (new_str)
	{
		status = SUCCESS;
		*buffer = new_str;
	}
	return (status);
}

int	ft_expansion_join_var(t_data *data,
	const char *str, char **buffer, size_t *i)
{
	int		status;
	char	*new_str;
	char	*content_name;

	status = BAD_PARAMETER;
	new_str = NULL;
	content_name = NULL;
	if (str && data && i && buffer)
	{
		status = ft_expansion_get_content(data, str, &content_name, i);
		if (status == SUCCESS && content_name && *content_name && *buffer)
			status = ft_expansion_join(content_name, buffer);
		else if (status == SUCCESS && content_name && *content_name)
		{
			new_str = ft_strdup(content_name);
			if (new_str)
				*buffer = new_str;
			else
				status = MALLOC_FAIL;
		}
		free(content_name);
	}
	return (status);
}
