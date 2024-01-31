/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:48:43 by tlassere          #+#    #+#             */
/*   Updated: 2024/01/31 21:07:03 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param env environement variable
 * @param name he used to get pos but no free
 * @param all_str full line of the path, free if table is deleted
*/
int	ft_env_update(t_env *env, const char *name, char *all_str)
{
	int	ret;
	int	pos;

	ret = ENV_UPDATE_FAIL;
	if (name && all_str)
	{
		ret = ENV_UPDATE_SUCCESS;
		pos = ft_env_get_pos(*env, name);
		if (pos != -1)
		{
			free(env->envp[pos]);
			env->envp[pos] = all_str;
		}
		else
			ret = ENV_UPDATE_NONE;
	}
	return (ret);
}

/***
 * @param env environement variable
 * @param all_str all string put in env
*/
/*
int	ft_env_add(t_env *env, char *all_str)
{
	int		ret;
	char	*name;

	ret = ENV_FAIL;
	if (env && all_str)
	{
		name = ft_env_get_name(all_str);
		if (name && ft_env_get_pos(*env, name) != -1)
		{
			ret = ENV_SUCCESS;
				
		}
		if (name == NULL)
			ret = MALLOC_FAIL;
		else
			ret = ENV_FAIL;
		free(name);
	}
	return (ret);
}
*/
