/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 02:16:41 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/05 21:11:02 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, const char **envp)
{
	//t_env	env;
	
	ft_echo(argv + 1, NULL);
	//env = ft_env_init(envp);
	//ft_check_args_main(argc);
	//ft_use_line();
	//ft_env_free(&env);
	(void)argc;
	(void)envp;
	(void)argv;
	return (0);
}
