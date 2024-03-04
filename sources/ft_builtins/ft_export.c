/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:27:00 by bcheronn          #+#    #+#             */
/*   Updated: 2024/03/04 17:46:21 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_export_is_valid(const char *name)
{
	int	ret;

	ret = FALSE;
	if (name && *name)
	{
		if (*name == '_' || ft_isalpha(*name))
		{
			name++;
			ret = TRUE;
			while (*name && ret)
			{
				if (*name != '_' && !ft_isalnum(*name))
					ret = FALSE;
				name++;
			}
		}
	}
	return (ret);
}

static int	ft_export_to_env(char *arg, t_env *env)
{
	int		ret;
	char	*name;

	name = ft_env_get_name(arg);
	if (name)
	{
		ret = ft_env_tab_del(&env->export, name);
		if (ret != MALLOC_FAIL)
			ret = ft_env_add(env, arg);
		free(name);
	}
	else
		ret = MALLOC_FAIL;
	return (ret);
}

// Update an existing variable or add it to **envp
static int	ft_export_update_env(char *arg, t_env *env)
{
	int		ret;
	char	*name;

	ret = FAIL;
	name = ft_env_get_name(arg);
	if (name)
	{
		if (ft_env_tab_get_pos(env->envp, name) == ENV_NOT_SET)
			ret = ft_env_add(env, arg);
		else
			ret = ft_env_update(env, name, arg);
		free(name);
	}
	return (ret);
}

static int	ft_export_process(char *arg, t_env *env)
{
	int		ret;
	char	*name;

	ret = FAIL;
	name = ft_env_get_name(arg);
	if (ft_export_is_valid(name))
	{
		ft_unsetting_path(arg, env);
		if (ft_strchr(arg, '='))
		{
			if (ft_env_tab_get_pos(env->export, name) != ENV_NOT_SET)
				ret = ft_export_to_env(arg, env);
			else
				ret = ft_export_update_env(arg, env);
		}
		else if (ft_env_tab_get_pos(env->envp, arg) == ENV_NOT_SET)
			ret = ft_env_tab_add(&env->export, arg);
	}
	else
		ft_fprintf(STDERR, "minishell: export: `%s': not a valid identifier\n",
			arg);
	if (name)
		free(name);
	return (ret);
}

int	ft_export(char **argv, t_env *env)
{
	int	exit_code;
	int	success;

	exit_code = FAIL;
	success = TRUE;
	if (env)
	{
		if (argv && argv[0] && argv[1])
		{
			argv++;
			exit_code = SUCCESS;
			while (argv[0] && exit_code != MALLOC_FAIL)
			{
				exit_code = ft_export_process(argv++[0], env);
				if (exit_code != SUCCESS)
					success = FAIL;
			}
			if (exit_code != MALLOC_FAIL && success == FAIL)
				exit_code = FAIL;
		}
		else
			exit_code = ft_export_print(env);
	}
	return (exit_code);
}
