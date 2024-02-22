/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:38:06 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/22 22:26:39 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec_iter_lst(t_data *data, int (*f)(t_data *, t_list *))
{
	int		status;
	t_list	*lst;

	status = BAD_PARAMETER;
	if (data)
	{
		status = SUCCESS;
		lst = data->words;
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

int	ft_exec(t_data *data)
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
