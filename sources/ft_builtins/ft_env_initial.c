/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_initial.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:28:56 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/29 22:13:58 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_env_init_pwd(t_env *env)
{
	char	*pwd;
	int		ret;

	ret = MALLOC_FAIL;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ret = ENV_SUCCESS;
		env->pwd = pwd;
	}
	return (ret);
}

char	**ft_init_table(void)
{
	char	**table;

	table = malloc(sizeof(char *));
	if (table)
		*table = NULL;
	return (table);
}

static int	ft_env_init_export(t_env *env)
{
	int		ret;
	char	**export;

	ret = MALLOC_FAIL;
	export = ft_init_table();
	if (export)
	{
		env->export = export;
		ret = ENV_SUCCESS;
	}
	return (ret);
}

int	ft_env_init_value(t_env *env)
{
	int	ret;

	ret = MALLOC_FAIL;
	if (env)
	{
		if (ft_env_init_shlvl(env) == ENV_SUCCESS
			&& ft_env_init_pwd(env) == ENV_SUCCESS
			&& ft_env_init_export(env) == ENV_SUCCESS)
			ret = ENV_SUCCESS;
	}
	return (ret);
}
