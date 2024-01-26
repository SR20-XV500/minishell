/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:56:50 by tlassere          #+#    #+#             */
/*   Updated: 2024/01/26 01:19:55 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_args_main(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd("Usage: arguments are not taken into consideration\n", 2);
	}
}
