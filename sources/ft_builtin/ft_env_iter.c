/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:48:43 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/01 20:14:16 by tlassere         ###   ########.fr       */
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


static int	ft_env_add_content(t_env *env, const char *all_str)
{
	int		ret;
	char	**table;

	ret = MALLOC_FAIL;	
	table = ft_tab_join(env->envp, all_str);
	if (table)
	{
		ret = ENV_SUCCESS;
		ft_tab_free(env->envp);
		env->envp = table;
	}
	return (ret);
}

/**
 * @param env environement variable
 * @param all_str dump to add in table
 */
int	ft_env_add(t_env *env, const char *all_str)
{
	int		ret;
	char	*name;

	ret = ENV_BAD_PARAMETER;
	if (env && all_str)
	{
		name = ft_env_get_name(all_str);
		if (name && ft_env_get_pos(*env, name) == -1)
			ret = ft_env_add_content(env, all_str);
		else if (name == NULL)
			ret = MALLOC_FAIL;
		else
			ret = ENV_EXISTING_VARIABLE;
		free(name);
	}
	return (ret);
}

//int	ft_env_del(t_env *env, const char *name)
//{
//	int	ret;
//	int	pos;

//	ret = ENV_BAD_PARAMETER;
//	if (env && name)
//	{
//		ret = 
//		pos = ft_env_get_pos(*env, name);
//		if (pos != -1)
//		{
			
//		}
//	}
//	return (ret);
//}
