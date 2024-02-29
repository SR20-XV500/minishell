/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:08:20 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/29 02:15:13 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec_dup(t_data *data, int *used_fd, int std_used)
{
	int	status;
	int	tmp_fd;

	status = SUCCESS;
	if (*used_fd > 2)
	{
		tmp_fd = dup(std_used);
		if (tmp_fd != FD_FAIL_OPEN)
		{
			if (data->dup_std[std_used] > 2)
				close(data->dup_std[std_used]);
			data->dup_std[std_used] = tmp_fd;
			if (dup2(*used_fd, std_used) == EXEC_DUP_FAIL)
				status = FAIL;
		}
	}
	return (status);
}

static int	ft_exec_dup_close_content(t_data *data, int *used_fd, int std_used)
{
	int	status;

	status = SUCCESS;
	if (data->dup_std[std_used] > 2)
	{
		if (dup2(data->dup_std[std_used], std_used) == EXEC_DUP_FAIL)
			status = FAIL;
		close(data->dup_std[std_used]);
		data->dup_std[std_used] = 0;
		close(*used_fd);
		*used_fd = 0;
	}
	return (status);
}

int	ft_exec_dup_close(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = SUCCESS;
		if (ft_exec_dup_close_content(data, &data->input_fd, STDIN) == FAIL)
			status = FAIL;
		if (ft_exec_dup_close_content(data, &data->output_fd, STDOUT) == FAIL)
			status = FAIL;
	}
	return (status);
}

int	ft_exec_dupbass(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = ft_exec_dup(data, &data->input_fd, STDIN);
		if (status == SUCCESS)
			status = ft_exec_dup(data, &data->output_fd, STDOUT);
	}
	return (status);
}
