/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:02:44 by tlassere          #+#    #+#             */
/*   Updated: 2024/01/30 18:39:12 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	ft_env_init(char **envp)
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	if (envp)
	{
		env.envp = ft_tab_dump(envp);
		env.path = ft_strdup(D_PATH);
	}
	return (env);
}

void	ft_env_free(t_env *env)
{
	if (env)
	{
		if (env->envp)
		{
			ft_tab_free(env->envp);
			env->envp = NULL;
		}
		if (env->path)
		{
			free(env->path);
			env->path = NULL;
		}
	}
}

int	ft_env_check(t_env *env)
{
	int	buffer;

	buffer = ENV_SUCCESS;
	if (env == NULL)
		buffer = ENV_FAIL;
	if (buffer == ENV_SUCCESS)
	{
		if (env->envp == NULL || env->path == NULL)
		{
			buffer = ENV_FAIL;
			ft_env_free(env);
		}
	}
	return (buffer);
}
