/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 02:16:41 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/07 00:46:55 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, const char **envp)
{
	t_env	env;

	ft_check_args_main(argc);
	if (ft_signal() == SIGNAL_HANDLING)
	{
		env = ft_env_init(envp);
		ft_use_line();
		ft_env_free(&env);
	}
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
