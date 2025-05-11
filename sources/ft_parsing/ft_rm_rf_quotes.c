/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_rf_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:41:39 by tlassere          #+#    #+#             */
/*   Updated: 2025/05/06 00:09:36 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quotes_remove(char *str)
{
	char	*buffer;

	buffer = NULL;
	if (str)
	{
		while (*str)
		{
			if (*str == '\"' && ft_strchr(str + 1, '\"'))
				buffer = ft_strchr(str + 1, '\"');
			else if (*str == '\'' && ft_strchr(str + 1, '\''))
				buffer = ft_strchr(str + 1, '\'');
			else
				buffer = NULL;
			if (buffer)
			{
				ft_memmove(buffer, buffer + 1, ft_strlen(buffer));
				ft_memmove(str, str + 1, ft_strlen(str));
				str = buffer - 1;
			}
			else
				str++;
		}
	}
	return (SUCCESS);
}
