/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:56:50 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/09 00:53:14 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_args_main(int argc)
{
	if (argc != 1)
	{
		ft_fprintf(STDERR,
			"Usage: arguments are not taken into consideration\n");
	}
}
