/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_true.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:38:33 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/29 21:22:47 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// else if (ft_strncmp("exit", cmd.path, 5) == CMP_EGAL)

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
		status = ft_export(cmd.argv, data->env);
	else if (ft_strncmp("unset", cmd.path, 6) == CMP_EGAL)
		status = ft_unset(cmd.argv, data->env);
	else if (ft_strncmp("env", cmd.path, 4) == CMP_EGAL)
		status = ft_env((const char **)cmd.envp);
	return (status);
}

static void	ft_exec_cmd_system_for_kids(t_data *data, const t_cmd_content cmd,
		const char *name)
{
	char	*buffer_name;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	buffer_name = ft_strdup(name);
	ft_data_free(&data);
	clear_history();
	if (buffer_name == NULL || execve(cmd.path, cmd.argv, cmd.envp))
	{
		ft_fprintf(STDERR, "minishell: ");
		perror(buffer_name);
	}
	free(buffer_name);
	ft_tab_free(cmd.argv);
	ft_tab_free(cmd.envp);
	free(cmd.path);
	exit(EXEC_CMD_NOT_FOUND);
}

static int	ft_exec_cmd_system(t_data *data, const t_cmd_content cmd,
		const char *name)
{
	pid_t	fork_pid;
	int		status;

	fork_pid = fork();
	status = SUCCESS;
	if (fork_pid == CHILDREN)
		ft_exec_cmd_system_for_kids(data, cmd, name);
	else if (fork_pid > CHILDREN)
		waitpid(fork_pid, &status, NO_OPTION);
	if (fork_pid == CHILDREN_FAIL)
		perror("minishell: ");
	return (status);
}

int	ft_exec_cmd_true(t_data *data, const t_cmd_content cmd, const char *name)
{
	int	status;

	status = BAD_PARAMETER;
	if (data && cmd.argv && *(cmd.argv) && cmd.envp && cmd.path)
	{
		status = SUCCESS;
		if (ft_is_builtin(cmd.path) == SUCCESS)
			status = ft_exec_cmd_builtin(data, cmd);
		else
			status = ft_exec_cmd_system(data, cmd, name);
		data->env->exit_status = status % EXIT_MODE;
	}
	return (status);
}
