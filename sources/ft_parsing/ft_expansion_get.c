/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_get.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 00:06:42 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/17 13:43:37 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_expansion_add_car(char *str, int car, char **buffer)
{
	char	*new_str;
	size_t	size;
	int		status;

	new_str = NULL;
	status = BAD_PARAMETER;
	if (buffer)
	{
		if (str == NULL)
			str = "";
		status = MALLOC_FAIL;
		size = ft_strlen(str) + 2;
		new_str = malloc(size * sizeof(char));
		if (new_str && buffer)
		{
			status = SUCCESS;
			ft_memmove(new_str, str, size - 2);
			new_str[size - 2] = car;
			new_str[size - 1] = '\0';
		}
		*buffer = new_str;
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
		if (ft_env_get_pos(*(data->env), name + 1) != -1
			|| ft_strncmp(name, "$?", 3) == CMP_EGAL)
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
	if (str[sub] == '$')
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
	ft_printf("%s\n", str);
	new_str = ft_strjoin(*buffer, str);
	if (new_str)
	{
		status = SUCCESS;
		*buffer = new_str;
	}
	return (status);
}

static int	ft_expansion_join_var(t_data *data,
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
		if (status == SUCCESS && content_name && *buffer)
			status = ft_expansion_join(content_name, buffer);
		else if (status == SUCCESS && content_name)
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

char	*ft_expansion_get_str(t_data *data, const char *str)
{
	char	*new_str;
	char	*buffer;
	int		status;
	size_t	i;

	new_str = NULL;
	buffer = NULL;
	status = SUCCESS;
	i = 0;
	if (str && data)
	{
		while (str[i] && status == SUCCESS)
		{
			if (ft_expansion_is_word(str + i) == SUCCESS)
				status = ft_expansion_join_var(data, str + i, &buffer, &i);
			else
				status = ft_expansion_add_car(buffer, str[i], &buffer);
			if (new_str != buffer)
				free(new_str);
			new_str = buffer;
			i++;
		}
		if (status != SUCCESS)
		{
			free(new_str);
			new_str = NULL;
		}
	}
	return (new_str);
}
