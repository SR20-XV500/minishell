/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:14:15 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/12 22:25:37 by tlassere         ###   ########.fr       */
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
		ft_printf("a");
		if (ret == SUCCESS)
			ret = ft_check_lst(data);
	}
	return (ret);
}
