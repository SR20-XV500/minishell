/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 02:20:14 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/20 02:20:35 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec_redirect_fd_err(int fd, const char *err_str)
{
	int	status;

	status = SUCCESS;
	if (fd == -1)
	{
		status = FAIL;
		ft_fprintf(STDERR, "minishell: ");
		perror(err_str);
	}
	return (status);
}

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
			open_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC);
		else
			open_fd = open(path, O_WRONLY | O_CREAT | O_APPEND);
		if (open_fd)
		{
			if (*change_fd > 2)
				close(*change_fd);
			*change_fd = open_fd;
		}
		status = ft_exec_redirect_fd_err(open_fd, err_str);
	}
	return (status);
}
