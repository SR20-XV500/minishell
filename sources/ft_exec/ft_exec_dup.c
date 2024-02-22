/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:08:20 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/22 22:37:01 by tlassere         ###   ########.fr       */
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

int	ft_exec_dup_close(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = SUCCESS;
		if (data->dup_std[STDIN] > 2)
		{
			if (dup2(data->dup_std[STDIN], STDIN) == EXEC_DUP_FAIL)
				status = FAIL;
			close(data->dup_std[STDIN]);
			data->dup_std[STDIN] = 0;
			close(data->input_fd);
			data->input_fd = 0;
		}
		if (data->dup_std[STDOUT] > 2)
		{
			if (dup2(data->dup_std[STDOUT], STDOUT) == EXEC_DUP_FAIL)
				status = FAIL;
			close(data->dup_std[STDOUT]);
			data->dup_std[STDOUT] = 0;
			close(data->output_fd);
			data->output_fd = 0;
		}
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
