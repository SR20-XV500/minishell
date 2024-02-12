/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:14:15 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/12 15:18:20 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser(t_data *data, const char *str)
{
	int	ret;

	ret = BAD_PARAMETER;
	if (data && str)
	{
		ret = ft_parser_use_line(data, str);
	}
	return (ret);
}
