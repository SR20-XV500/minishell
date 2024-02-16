/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_get _str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 00:06:42 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/17 00:57:26 by tlassere         ###   ########.fr       */
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
	if (str)
	{
		status = MALLOC_FAIL;
		size = ft_strlen(str) + 2;
		new_str = malloc(size * sizeof(char));
		if (new_str && buffer)
		{
			status = SUCCESS;
			ft_memmove(new_str, str, size * sizeof(char));
			new_str[new_str - 2] = car;
			new_str[new_str - 2] = '\0';
			*buffer = new_str;
		}
	}
	return (status);
}

char	*ft_expansion_get_str(const char *str)
{
	char	*new_str;
	char	*buffer;
	int		status;
	size_t	i;

	new_str = NULL;
	status = SUCCESS;
	i = 0;
	if (str)
	{
		while (str[i] && status == SUCCESS)
		{
			if (ft_expansion_is_word(str + i) == SUCCESS)
			{
			}
			else
				ft_expansion_add_car(str)
			i++;
		}
	}
	return (new_str);
}
