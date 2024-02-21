/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_true.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:38:33 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/21 21:38:42 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//else if (ft_strncmp("exit", cmd.path, 5) == CMP_EGAL)
//else if (ft_strncmp("unset", cmd.path, 6) == CMP_EGAL)
//else if (ft_strncmp("env", cmd.path, 4) == CMP_EGAL)

static int	ft_exec_cmd_builtin(t_data *data, const t_cmd_content cmd)
{
	int	status;

	status = FAIL;
	if (ft_strncmp("cd", cmd.path, 3) == CMP_EGAL)
		status = ft_cd(cmd.argv, cmd.envp);
	else if (ft_strncmp("echo", cmd.path, 5) == CMP_EGAL)
		status = ft_echo(cmd.argv, cmd.envp);
	else if (ft_strncmp("pwd", cmd.path, 4) == CMP_EGAL)
		status = ft_pwd(cmd.argv, cmd.envp);
	else if (ft_strncmp("export", cmd.path, 7) == CMP_EGAL)
		status = ft_export(cmd.argv, cmd.envp);
	(void)data;
	return (status);
}

int	ft_exec_cmd_true(t_data *data, const t_cmd_content cmd)
{
	int	status;

	status = BAD_PARAMETER;
	if (data && cmd.argv && *(cmd.argv) && cmd.envp && cmd.path)
	{
		status = SUCCESS;
		if (ft_is_builtin(cmd.path) == SUCCESS)
			ft_exec_cmd_builtin(data, cmd);
	}
	return (status);
}
