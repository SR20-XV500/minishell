/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 02:16:41 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/06 18:20:14 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, const char **envp)
{
	t_env	env;
	
	//ft_echo(argv, NULL);
	env = ft_env_init(envp);
	//ft_check_args_main(argc);
	//ft_use_line();
	printf("%d\n", ft_env_get_pos(env, "HOME"));
	ft_env_free(&env);
	(void)argc;
	(void)envp;
	(void)argv;
	return (0);
}
