/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:54:23 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/05 02:52:19 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_change_pwd(t_env *env)
{
	char	*str;
	char	*get_content;

	if (ft_env_tab_get_pos(env->export, "OLDPWD") != ENV_NOT_SET
		|| ft_env_tab_get_pos(env->envp, "OLDPWD") != ENV_NOT_SET)
	{
		if (ft_env_tab_get_pos(env->envp, "PWD") != ENV_NOT_SET)
		{
			get_content = ft_env_tab_get_content(env->envp, "PWD");
			if (get_content)
			{
				str = ft_strjoin("OLDPWD=", get_content);
				if (str)
					ft_export_process(str, env);
				if (str)
					free(str);
				free(get_content);
			}
		}
		else
		{
			if (ft_env_del(env, "OLDPWD") == SUCCESS)
				ft_env_tab_add(&env->envp, "OLDPWD");
		}
	}
}

static int	ft_cd_update_env(const char *path, t_env *env)
{
	int		status;
	char	*buffer;

	buffer = NULL;
	status = SUCCESS;
	if (path && env)
	{
		ft_cd_change_pwd(env);
		if (ft_env_tab_get_pos(env->envp, "PWD") != ENV_NOT_SET
			|| ft_env_tab_get_pos(env->envp, "PWD") != ENV_NOT_SET)
		{
			buffer = ft_strjoin("PWD=", path);
			if (buffer)
				status = ft_export_process(buffer, env);
		}
	}
	if (buffer)
		free(buffer);
	return (status);
}

int	ft_cd_update_path(const char *new_path, t_env *env)
{
	int		status;
	char	*buffer;
	char	*buffer_export;

	status = FAIL;
	buffer = NULL;
	buffer_export = NULL;
	if (new_path && env)
	{
		buffer = ft_strdup(new_path);
		if (buffer)
		{
			free(env->pwd);
			env->pwd = buffer;
			if (ft_cd_update_env(new_path, env) == SUCCESS)
				status = SUCCESS;
		}
	}
	return (status);
}