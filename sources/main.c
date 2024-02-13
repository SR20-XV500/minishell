/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 02:16:41 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/13 02:11:29 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, const char **envp)
{
	t_data	*data;

	ft_check_args_main(argc);
	data = ft_data_get(envp);
	if (data && ft_signal() == SIGNAL_HANDLING)
	{
		ft_use_line(data);
		ft_data_free(&data);
	}
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
