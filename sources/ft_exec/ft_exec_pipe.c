/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 22:39:39 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/24 19:31:11 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipe(int *fds, int len)
{
	if (fds && len > 0)
	{
		len *= 2;
		while (len)
		{
			len--;
			if (*(fds + len) > 2)
			{
				close(*(fds + len));
				*(fds + len) = 0;
			}
		}
	}
}

static int	ft_set_pipe(int *fd, int len)
{
	int	i;
	int	status;

	i = 0;
	status = SUCCESS;
	while (i < len && status == SUCCESS)
	{
		if (pipe(fd + i * 2) != SUCCESS)
			status = FAIL;
		i++;
	}
	if (status == FAIL)
		ft_close_pipe(fd, i);
	return (status);
}

static int	ft_pipe_make_children(t_data *data, int *fds, int len)
{
	int		status;
	pid_t	*children;

	status = BAD_PARAMETER;
	if (data && fds && len > 0)
	{
		len++;
		status = MALLOC_FAIL;
		children = malloc(sizeof(pid_t) * len);
		if (children)
		{
			ft_bzero(children, sizeof(pid_t) * len);
			status = ft_crazy_children(data, fds, len, children);
			free(children);
		}
	}
	return (status);
}

int	ft_exec_pipe(t_data *data)
{
	int	status;
	int	*pipe_fd;
	int	len;

	status = BAD_PARAMETER;
	if (data)
	{
		status = MALLOC_FAIL;
		len = ft_word_count(data->words, D_PIPE);
		pipe_fd = malloc(sizeof(int) * 2 * len);
		if (pipe_fd)
		{
			status = ft_set_pipe(pipe_fd, len);
			if (status == SUCCESS)
			{
				status = ft_pipe_make_children(data, pipe_fd, len);
				ft_close_pipe(pipe_fd, len);
			}
			free(pipe_fd);
		}
	}
	return (status);
}
