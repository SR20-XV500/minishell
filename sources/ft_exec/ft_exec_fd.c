/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 02:20:14 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/20 15:50:17 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec_redirect_fd_err(t_data *data, int fd,
	const char *err_str, const char *path)
{
	int	status;

	status = SUCCESS;
	if (fd == -1)
	{
		status = FAIL;
		ft_fprintf(STDERR, "minishell: ");
		perror(err_str);
		data->env->exit_status = 1;
	}
	else if (ft_is_directory(path) == SUCCESS)
	{
		status = FAIL;
		ft_fprintf(STDERR, "minishell: %s: Is a directory\n", err_str);
		data->env->exit_status = 1;
	}
	return (status);
}

/**
 * in opens for redirection out, flags 0644 is specified.
 * its meaning is :
 * 0 : to indicate that it is a permision flag which changes
 *	the way the prgram includes the following numbers
 *
 * 6: to open the user's read and write functions
 *
 * 4: to open in read mode in the group
 *
 * 4: to open in read mode in the others
*/
int	ft_exec_redirect_fd(t_data *data, int type,
	const char *path, const char *err_str)
{
	int	status;
	int	open_fd;
	int	*change_fd;

	status = BAD_PARAMETER;
	if (data && path && err_str)
	{
		change_fd = &(data->output_fd);
		if (type == D_INPUT)
			change_fd = &(data->input_fd);
		if (type == D_INPUT)
			open_fd = open(path, O_RDONLY);
		else if (type == D_OUTPUT_NEW)
			open_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			open_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (open_fd)
		{
			if (*change_fd > 2)
				close(*change_fd);
			*change_fd = open_fd;
		}
		status = ft_exec_redirect_fd_err(data, open_fd, err_str, path);
	}
	return (status);
}
