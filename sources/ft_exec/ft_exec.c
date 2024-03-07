/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:38:06 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/07 01:06:33 by tlassere         ###   ########.fr       */
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

int	ft_exec_basic(t_data *data, t_list *lst_start)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = ft_exec_iter_lst(data, lst_start, &ft_exec_redirect);
		if (status == SUCCESS
			&& ft_redirect_priority(lst_start) == PRIORITY_HERE_DOC)
			status = ft_exec_here_doc_redirect(data, lst_start);
		if (status == SUCCESS)
			status = ft_exec_dupbass(data);
		if (status == SUCCESS)
			status = ft_exec_iter_lst(data, lst_start, &ft_exec_cmd);
		if (ft_exec_dup_close(data) == FAIL)
			status = FAIL;
	}
	return (status);
}

int	ft_word_count(t_list *lst, int type)
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

int	ft_exec(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = ft_exec_here_doc(data);
		if (status == SUCCESS)
		{
			status = ft_signal_exec();
		}
		if (status == SUCCESS)
		{
			if (ft_word_count(data->words, D_PIPE))
				status = ft_exec_pipe(data);
			else
				status = ft_exec_basic(data, data->words);
		}
	}
	return (status);
}
