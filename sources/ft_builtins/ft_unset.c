/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:39:18 by bcheronn          #+#    #+#             */
/*   Updated: 2024/03/06 19:19:09 by bcheronn         ###   ########.fr       */
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
	}
	ft_unset_path(name, env);
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
