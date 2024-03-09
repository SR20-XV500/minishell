/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 02:16:41 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/09 00:53:44 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, const char **envp)
{
	t_data	*data;
	int		exit_status;

	(void)argv;
	ft_check_args_main(argc);
	data = ft_data_get(envp);
	exit_status = 0;
	if (data)
	{
		if (ft_signal_interactive() == SIGNAL_HANDLING)
			ft_use_line(data);
		exit_status = data->env->exit_status;
		ft_data_free(&data);
	}
	if (g_signal_handle == SIGINT_SIGNAL)
		exit_status = g_signal_handle;
	return (exit_status);
}
