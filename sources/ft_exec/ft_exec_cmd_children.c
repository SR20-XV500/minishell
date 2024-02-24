/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_children.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:18:48 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/24 14:48:01 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_kill_children(pid_t *children, int len)
{
	if (children && len > 0)
	{
		while (len)
		{
			len--;
			kill(children[len], SIGKILL);
		}
	}
}

static void ft_close_pipe_no_used(int *fds, int std[2], int len)
{
	len *= 2;
	while (len)
	{
		len--;
		if (*(fds + len) != std[STDIN] && *(fds+ len) != std[STDOUT]
			&& *(fds + len) > 2)
		{
			close(*(fds + len));
			*(fds + len) = 0;
		}
	}
}

static int	ft_exec_dup_pipe(int *fds, int pos, int len)
{
	int	status;
	int	std[2];

	status = BAD_PARAMETER;
	if (fds && pos >= 0 && len > 0)
	{
		status = SUCCESS;
		std[STDIN] = STDIN;
		std[STDOUT] = STDOUT;
		if (pos != 0)
		{
			std[STDIN] = *(fds + pos / 2 + STDIN);
		}
		if (pos != len -1)
		{
			std[STDOUT] = *(fds + pos / 2 + STDOUT);
		}
		//if (pos == 0)
		//{
		//	std[STDOUT] = *(fds + 1);
		//	//close(*fds);
		//}
		//if (pos == 1)
		//{
		//	std[STDIN] = *(fds + 0);
		//	//close(*(fds + 1));
		//}
		ft_close_pipe_no_used(fds, std, len - 1);
		if (dup2(std[STDIN], STDIN) == EXEC_DUP_FAIL
			|| dup2(std[STDOUT], STDOUT) == EXEC_DUP_FAIL)
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

	exit_status = 0;
	if (data && fds && len)
	{
		if (ft_exec_dup_pipe(fds, pos, len) == SUCCESS)
			ft_exec_basic(data, ft_exec_get_cmd(data, pos));
		exit_status = data->env->exit_status;
	}
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
			ft_kill_children(children, index);
		else
			ft_wait_children(data, children, len);
	}
	return (status);
}
