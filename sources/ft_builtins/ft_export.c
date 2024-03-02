/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:27:00 by bcheronn          #+#    #+#             */
/*   Updated: 2024/03/02 16:20:25 by bcheronn         ###   ########.fr       */
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
	ret = ft_env_tab_del(&env->export, name);
	if (ret != MALLOC_FAIL)
		ret = ft_env_add(env, arg);
	if (name)
		free(name);
	return (ret);
}

// Update an existing variable or add it to **envp
static int	ft_export_update_env(char *arg, t_env *env)
{
	int	ret;

	ret = FAIL;
	if (ft_env_tab_get_pos(env->envp, ft_env_get_name(arg)) == -1)
		ret = ft_env_add(env, arg);
	else
		ret = ft_env_update(env, ft_env_get_name(arg), arg);
	ft_fprintf(STDERR, "export_update_env env_tab_del ret: %d\n", ret);
	return (ret);
}

// TODO: export VAR:
// TODO: What do we do when a ft_fprintf (ie. on STDERR) fails?
// TODO: Kill all leaks (ft_env_get_name)
static int	ft_export_process(char *arg, t_env *env)
{
	int	ret;

	ret = FAIL;
	if (ft_export_is_valid(ft_env_get_name(arg)))
	{
		if (ft_strchr(arg, '='))
		{
			ret = ft_env_tab_get_pos(env->export, ft_env_get_name(arg));
			ft_fprintf(STDERR, "export_process env_tab_del ret: %d\n", ret);
			if (ft_env_tab_get_pos(env->export, ft_env_get_name(arg)) != -1)
				ret = ft_export_to_env(arg, env);
			else
				ret = ft_export_update_env(arg, env);
		}
		else
		{
			if (ft_env_tab_get_pos(env->envp, arg) == -1)
				ret = ft_env_tab_add(&env->export, arg);
		}
	}
	else
		ft_fprintf(STDERR, "minishell: export: `%s': not a valid identifier\n",
			arg);
	return (ret);
}

// TODO: Check the various exit codes for ft_export_process (MALLOC_FAIL)
int	ft_export(char **argv, t_env *env)
{
	int	exit_code;

	exit_code = FAIL;
	if (env)
	{
		if (argv && argv[0] && argv[1])
		{
			argv++;
			exit_code = SUCCESS;
			while (argv[0] && exit_code != MALLOC_FAIL)
			{
				exit_code = ft_export_process(argv[0], env);
				argv++;
			}
		}
		else
			exit_code = ft_export_print(env);
	}
	return (exit_code);
}
