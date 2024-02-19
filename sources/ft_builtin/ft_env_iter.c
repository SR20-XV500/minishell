/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:48:43 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/19 22:36:25 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @param env environement variable
 * @param name he used to get pos but no free
 * @param all_str full line of the path, this variable are dump
 * @return
 * MALLOC_FAIL;
 * ENV_UPDATE_FAIL -> if arguments is bad;
 * ENV_UPDATE_SUCCESS;
 * ENV_UPDATE_NONE -> if variable don't existe
*/
int	ft_env_update(t_env *env, const char *name, const char *all_str)
{
	int		ret;
	int		pos;
	char	*new_str;	

	ret = ENV_UPDATE_FAIL;
	if (name && all_str)
	{
		ret = ENV_UPDATE_SUCCESS;
		pos = ft_env_get_pos(*env, name);
		new_str = ft_strdup(all_str);
		if (new_str == NULL)
			ret = MALLOC_FAIL;
		else if (pos != -1)
		{
			free(env->envp[pos]);
			env->envp[pos] = new_str;
		}
		else
			ret = ENV_UPDATE_NONE;
	}
	return (ret);
}

/**
 * @param env environement variable
 * @param all_str dump to add in table
 */
int	ft_env_add(t_env *env, const char *all_str)
{
	int	status;

	status = BAD_PARAMETER;
	if (env && all_str)
		status = ft_env_tab_add(&env->envp, all_str);
	return (status);
}

int	ft_env_del(t_env *env, const char *name)
{
	int	status;

	status = BAD_PARAMETER;
	if (env && name)
		status = ft_env_tab_del(&(env->envp), name);
	return (status);
}
