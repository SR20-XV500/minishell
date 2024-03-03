/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:39:18 by bcheronn          #+#    #+#             */
/*   Updated: 2024/03/03 19:33:46 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_unset_arg(const char *name, t_env *env)
{
	int	status;

	status = SUCCESS;
	if (name)
	{
		if (ft_env_tab_get_pos(env->export, name) != ENV_NOT_SET)
			status = ft_env_tab_del(&env->export, name);
		else if (ft_env_tab_get_pos(env->envp, name) != ENV_NOT_SET)
			status = ft_env_tab_del(&env->envp, name);
		if (env->path && ft_strncmp("PATH", name, 5) == CMP_EGAL)
		{
			free(env->path);
			env->path = NULL;
		}
	}
	if (status != SUCCESS)
		status = FAIL;
	return (status);
}

int	ft_unset(char **argv, t_env *env)
{
	int	ret;

	ret = SUCCESS;
	if (env && argv && argv[0] && argv[1])
	{
		argv++;
		while (*argv)
		{
			if (ft_unset_arg(*argv, env) == FAIL)
				ret = FAIL;
			argv++;
		}
	}
	return (ret);
}
