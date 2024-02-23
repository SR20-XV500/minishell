/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:38:06 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/23 19:10:44 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec_iter_lst(t_data *data,
	t_list *lst_start, int (*f)(t_data *, t_list *))
{
	int		status;
	t_list	*lst;

	status = BAD_PARAMETER;
	if (data && f && lst_start)
	{
		status = SUCCESS;
		lst = lst_start;
		while (lst && status == SUCCESS)
		{
			status = (*f)(data, lst);
			lst = lst->next;
		}
		if (status == D_PIPE)
			status = SUCCESS;
	}
	return (status);
}

static int	ft_exec_basic(t_data *data, t_list *lst_start)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = ft_exec_iter_lst(data, lst_start, &ft_exec_redirect);
		if (status == SUCCESS)
			status = ft_exec_dupbass(data);
		if (status == SUCCESS)
			status = ft_exec_iter_lst(data, lst_start, &ft_exec_cmd);
		if (ft_exec_dup_close(data) == FAIL)
			status = FAIL;
	}
	return (status);
}

static int	ft_word_count(t_list *lst, int type)
{
	int		count;
	t_word	*word;

	count = 0;
	while (lst)
	{
		word = lst->content;
		if (word && word->type == type)
			count++;
		lst = lst->next;
	}
	return (count);
}

static void	ft_close_pipe(int *fds, int len)
{
	if (fds && len >0)
	{
		while (len)
		{
			len--;
			close(*(fds + len * 2));
			close(*(fds + (len * 2) + 1));
			*(fds + len * 2) = 0;
			*(fds + (len * 2) + 1) = 0;
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

static void	ft_wait_children(t_data *data, pid_t *children, int len)
{
	int	index;
	int	tmp;

	index = 0;
	tmp = 0;
	if (data && children && len > 0)
	{
		while (index < len)
		{
			waitpid(children[index], &tmp, 0);
			printf("exit:  %d\n", tmp % EXIT_MODE);
			data->env->exit_status = tmp % EXIT_MODE;
			index++;
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
			std[STDIN] = *(fds + pos * 2);
		if (pos != len - 1)
			std[STDOUT] = *(fds + pos * 2 + 1);
		if (dup2(std[STDIN], STDIN) == EXEC_DUP_FAIL
			|| dup2(std[STDOUT], STDOUT) == EXEC_DUP_FAIL)
			status = FAIL;
	}
	return (status);
}

static t_list *ft_exec_get_cmd(t_data *data, int pos)
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

static int	ft_crazy_children(t_data *data, int *fds, int len, pid_t *children)
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
		if (status == FAIL)
			ft_kill_children(children, index);
		else
			ft_wait_children(data, children, len);
	}
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

static int	ft_exec_pipe(t_data *data)
{
	int	status;
	int	*pipe_fd;
	int len;

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

int	ft_exec(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		if (ft_word_count(data->words, D_PIPE))
			status = ft_exec_pipe(data);
		else
			status = ft_exec_basic(data, data->words);
	}
	return (status);
}
