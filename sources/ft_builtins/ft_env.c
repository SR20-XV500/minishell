/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:02:44 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/21 21:51:36 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: set default OLDPWD, set default PWD

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
			if (ft_env_init_value(env) != ENV_SUCCESS
				|| ft_env_check(env) == ENV_FAIL)
			{
				ft_env_free(env);
				env = NULL;
			}
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
		if (env->export)
			ft_tab_free(env->export);
		if (env->path)
			free(env->path);
		if (env->pwd)
			free(env->pwd);
		env->path = NULL;
		env->envp = NULL;
		env->pwd = NULL;
		env->export = NULL;
		free(env);
	}
}

int	ft_env_check(t_env *env)
{
	int	buffer;

	buffer = ENV_FAIL;
	if (env)
	{
		if (env->envp && env->path && env->pwd)
			buffer = ENV_SUCCESS;
	}
	return (buffer);
}

int	ft_env(const char **envp)
{
	int	ret;

	ret = FAIL;
	if (envp && ft_printf("%w", envp) > 0)
		ret = SUCCESS;
	return (ret);
}
