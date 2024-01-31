/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 02:16:41 by tlassere          #+#    #+#             */
/*   Updated: 2024/01/31 21:07:29 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, const char **envp)
{
	t_env	env;

	//ft_check_args_main(argc);
	//ft_use_line();
	env = ft_env_init(envp);
	//ft_env_add(&env, argv[1]);
	ft_env_free(&env);
	(void)argv;
	(void)argc;
	return (0);
}
