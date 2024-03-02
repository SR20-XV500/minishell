/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expantion_get_str_func.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 01:24:12 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/02 18:25:02 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expansion_get_str_func(t_data *data, const char *str,
	int (*get_while)(t_data *, const char *, size_t *, char **))
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
			status = (*get_while)(data, str, &i, &buffer);
			if (new_str != buffer)
				free(new_str);
			new_str = buffer;
			i++;
		}
		if (status != SUCCESS)
			free(new_str);
		if (status != SUCCESS)
			new_str = NULL;
	}
	return (new_str);
}

char	*ft_expansion_get_str(t_data *data, const char *str)
{
	return (ft_expansion_get_str_func(data, str, &ft_expantion_get_while));
}
