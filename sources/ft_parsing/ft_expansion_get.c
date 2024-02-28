/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_get.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 00:06:42 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/28 01:35:33 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expansion_add_car(char *str, int car, char **buffer)
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

static int	ft_expansion_quote(const char *str, const char *current_car)
{
	int		status;
	char	*buffer;

	buffer = (char *)str;
	status = BAD_PARAMETER;
	if (str && current_car)
	{
		status = SUCCESS;
		while (buffer < current_car && *buffer)
		{
			status = SUCCESS;
			if (*buffer == '\"' && ft_strchr(buffer + 1, '\"'))
				buffer = ft_strchr(buffer + 1, '\"');
			else if (*buffer == '\'' && ft_strchr(buffer + 1, '\''))
			{
				buffer = ft_strchr(buffer + 1, '\'');
				status = FAIL;
			}
			buffer++;
		}
	}
	return (status);
}

int	ft_expantion_get_while(t_data *data,
	const char *str, size_t *i, char **buffer)
{
	int	status;

	if (ft_expansion_is_word(str + *i) == SUCCESS
		&& ft_expansion_quote(str, str + *i) == SUCCESS)
		status = ft_expansion_join_var(data, str + *i, buffer, i);
	else
		status = ft_expansion_add_car(*buffer, str[*i], buffer);
	return (status);
}

int	ft_expansion_str(t_data *data, const char *str, char **new_str)
{
	int	status;

	status = BAD_PARAMETER;
	if (str && new_str)
	{
		status = PARSER_EXPANSION_VAR_NO_CHANGE;
		if (ft_strchr(str, '$'))
		{
			status = PARSER_EXPANSION_VAR_CHANGE;
			*new_str = ft_expansion_get_str(data, str);
		}
	}
	return (status);
}
