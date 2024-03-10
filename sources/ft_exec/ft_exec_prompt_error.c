/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_prompt_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:23:36 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/10 23:01:30 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_display_error_execve(const t_cmd_content cmd, const char *buff)
{
	int	status;

	status = EXEC_CMD_NOT_FOUND;
	if (ft_is_directory(cmd.path) != SUCCESS || *buff == '\0')
	{
		ft_fprintf(STDERR, "minishell: ");
		if (*buff == '\0')
			ft_fprintf(STDERR, "'': command not found\n");
		else
			perror(buff);
		if (ft_is_file(cmd.path) == SUCCESS)
			status = EXEC_CMD_PERMISSION_DENIED;
	}
	else
	{
		ft_fprintf(STDERR, "minishell: %s: Is a directory\n", buff);
		status = EXEC_CMD_NOT_FOUND_DIR;
	}
	return (status);
}
