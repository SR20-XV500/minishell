/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_children.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:18:48 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/01 15:42:22 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_close_pipe_no_used(int *fds, int std[2], int len)
{
	int	status;

	status = SUCCESS;
	len *= 2;
	while (len && status == SUCCESS)
	{
		len--;
		if (fds[len] != std[STDIN] && fds[len] != std[STDOUT])
		{
			if (close(*(fds + len)) == -1)
				status = FAIL;
			*(fds + len) = 0;
		}
	}
	return (status);
}

static int	ft_exec_dup_pipe(int *fds, int pos, int len, int std[2])
{
	int	status;

	status = BAD_PARAMETER;
	if (fds && pos >= 0 && len > 0 && std)
	{
		status = SUCCESS;
		if (pos != 0)
			std[STDIN] = *(fds + (pos - 1) * 2 + STDIN);
		if (pos != len -1)
			std[STDOUT] = *(fds + pos * 2 + STDOUT);
		status = ft_close_pipe_no_used(fds, std, len - 1);
		if (status == SUCCESS && (dup2(std[STDIN], STDIN) == EXEC_DUP_FAIL
				|| dup2(std[STDOUT], STDOUT) == EXEC_DUP_FAIL))
			status = FAIL;
	}
	return (status);
}

static t_list	*ft_exec_get_cmd(t_data *data, int pos)
{
	t_word	*word;
	t_list	*lst;

	lst = NULL;
	if (data && pos >= 0)
	{
		lst = data->words;
		while (pos && lst->content)
		{
			word = lst->content;
			if (word->type == D_PIPE)
				pos--;
			lst = lst->next;
		}
		if (lst->content == NULL)
			lst = NULL;
	}
	return (lst);
}

static void	ft_exec_children_cmd(t_data *data, int *fds, int pos, int len)
{
	int	exit_status;
	int	buffer[2];

	buffer[STDIN] = STDIN;
	buffer[STDOUT] = STDOUT;
	exit_status = 0;
	if (data && fds && len)
	{
		if (ft_exec_dup_pipe(fds, pos, len, buffer) == SUCCESS)
		{
			free(fds);
			ft_exec_basic(data, ft_exec_get_cmd(data, pos));
		}
		exit_status = data->env->exit_status;
	}
	if (buffer[STDIN] > 2)
		close(buffer[STDIN]);
	if (buffer[STDOUT] > 2)
		close(buffer[STDOUT]);
	ft_data_free(&data);
	rl_clear_history();
	exit(exit_status);
}

int	ft_crazy_children(t_data *data, int *fds, int len, pid_t *children)
{
	int	status;
	int	index;

	status = BAD_PARAMETER;
	index = 0;
	if (data && fds && len > 0 && children)
	{
		status = SUCCESS;
		while (index < len && status == SUCCESS)
		{
			children[index] = fork();
			if (children[index] > -1 && children[index] == 0)
				ft_exec_children_cmd(data, fds, index, len);
			if (children[index] == -1)
				status = FAIL;
			index++;
		}
		ft_close_pipe(fds, len - 1);
		if (status == FAIL)
			ft_kill_children(children, index - 1);
		else
			ft_wait_children(data, children, len);
	}
	return (status);
}
