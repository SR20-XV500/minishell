/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:01:41 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/06 00:36:42 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(const char *cmd)
{
	int	status;

	status = BAD_PARAMETER;
	if (cmd)
	{
		status = FAIL;
		if (ft_strncmp("cd", cmd, 3) == CMP_EGAL
			|| ft_strncmp("echo", cmd, 5) == CMP_EGAL
			|| ft_strncmp("unset", cmd, 6) == CMP_EGAL
			|| ft_strncmp("export", cmd, 7) == CMP_EGAL
			|| ft_strncmp("exit", cmd, 5) == CMP_EGAL
			|| ft_strncmp("pwd", cmd, 4) == CMP_EGAL
			|| ft_strncmp("env", cmd, 4) == CMP_EGAL)
			status = SUCCESS;
	}
	return (status);
}

static void	ft_exec_cmd_error(t_data *data, const char *path, const char *cmd)
{
	if (data && path == NULL && cmd)
	{
		ft_fprintf(STDERR, "minishell: %s: command not found\n", cmd);
		data->env->exit_status = EXEC_CMD_NOT_FOUND;
	}
}

static char	*ft_exec_cmd_path_parser(t_data *data, const char *cmd_name,
	const char *path)
{
	char	*cmd;

	cmd = NULL;
	if (ft_is_builtin(cmd_name) == SUCCESS)
		cmd = ft_strdup(cmd_name);
	else
	{
		if (ft_strncmp("./", cmd_name, 2) == CMP_EGAL
			|| ft_strncmp("../", cmd_name, 3) == CMP_EGAL)
			cmd = ft_path_parser(data->env->pwd, cmd_name);
		else
			cmd = ft_path_multiple_file(path, cmd_name, data->env);
	}
	return (cmd);
}

char	*ft_exec_cmd_get_path(t_data *data, const char *cmd_name)
{
	char	*new_path;
	char	*path;
	char	*path_used;

	new_path = NULL;
	path = NULL;
	path_used = "./";
	if (data && cmd_name)
	{
		if (*cmd_name != '/')
			path = ft_env_get_content(*(data->env), "PATH");
		if (path && *path)
			path_used = path;
		if (*cmd_name == '/')
			new_path = ft_strdup(cmd_name);
		else
			new_path = ft_exec_cmd_path_parser(data, cmd_name, path_used);
		free(path);
		ft_exec_cmd_error(data, new_path, cmd_name);
	}
	return (new_path);
}
