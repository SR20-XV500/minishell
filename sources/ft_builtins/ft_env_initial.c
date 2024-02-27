/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_initial.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:28:56 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/28 00:20:55 by bcheronn         ###   ########.fr       */
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

int	ft_env_init_value(t_env *env)
{
	int	ret;

	ret = MALLOC_FAIL;
	if (env)
	{
		if (ft_env_init_shlvl(env) == ENV_SUCCESS
			&& ft_env_init_pwd(env) == ENV_SUCCESS)
			ret = ENV_SUCCESS;
	}
	return (ret);
}
