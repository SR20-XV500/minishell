/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:02:44 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/08 00:01:41 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_env_init(const char **envp)
{
	t_env	*env;

	env = NULL;
	if (envp)
	{
		env = malloc(sizeof(t_env));
		if (env)
		{
			ft_bzero(env, sizeof(t_env));
			env->envp = ft_tab_dump((char **)envp);
			env->path = ft_strdup(D_PATH);
			if (ft_env_init_value(env) != ENV_SUCCESS)
				ft_env_free(env);
			if (ft_env_check(env) == ENV_FAIL)
				env = NULL;
		}
	}
	return (env);
}

void	ft_env_free(t_env *env)
{
	if (env)
	{
		if (env->envp)
			ft_tab_free(env->envp);
		if (env->path)
			free(env->path);
		if (env->pwd)
			free(env->pwd);
		env->path = NULL;
		env->envp = NULL;
		env->pwd = NULL;
		free(env);
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
		if (env->envp == NULL || env->path == NULL || env->pwd == NULL)
		{
			buffer = ENV_FAIL;
			ft_env_free(env);
		}
	}
	return (buffer);
}
