/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:38:06 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/20 22:01:26 by tlassere         ###   ########.fr       */
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

static int	ft_exec_cmd(t_data *data, t_list *lst)
{
	int		status;
	int		type;
	char	*path;
	//char	**argv;

	status = BAD_PARAMETER;
	path = NULL;
	//argv = NULL
	if (data && lst && lst->content)
	{
		status = SUCCESS;
		type = ((t_word *)lst->content)->type;
		if (type == TY_CMD)
		{
			path = ft_exec_cmd_get_path(data, ((t_word *)lst->content)->word);
			//argv = ft_exec_cmd_get_argv();
			printf("hello le path : %s\n", path);
		}
		else if (type == D_PIPE)
			status = D_PIPE;
		free(path);
		//ft_tab_free(argv);
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
			status = ft_exec_iter_lst(data, &ft_exec_cmd);
	}
	return (status);
}
