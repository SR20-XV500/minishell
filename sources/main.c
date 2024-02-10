/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 02:16:41 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/10 13:26:23 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, const char **envp)
{
	t_env	*env;

	ft_check_args_main(argc);
	env = NULL;
	if (ft_signal() == SIGNAL_HANDLING)
	{
		env = ft_env_init(envp);
		if (env)
		{
			ft_pwd_init(&env->pwd);
			ft_cd(argv, env->envp);
			ft_use_line();
			ft_env_free(env);
		}
	}
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
