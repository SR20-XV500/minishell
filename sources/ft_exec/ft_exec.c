/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:38:06 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/23 13:30:17 by tlassere         ###   ########.fr       */
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
		status = ft_exec_iter_lst(data, &ft_exec_redirect);
		if (status == SUCCESS)
			status = ft_exec_dupbass(data);
		if (status == SUCCESS)
			status = ft_exec_iter_lst(data, &ft_exec_cmd);
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
	}
	if (status == FAIL)
	{
		while (i)
		{
			i--;
			close(fd + i * 2);
			close(fd + (i * 2) + 1);
		}
		ft_bzero(fd, len * sizeof(int));
	}
	return (FAIL);
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
				
			}
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
