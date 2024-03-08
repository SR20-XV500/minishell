/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:35:33 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/08 16:42:02 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirect_priority(t_list *lst)
{
	int	priority;

	priority = NO_PRIORITY;
	while (lst && lst->content && ((t_word *)lst->content)->type != D_PIPE)
	{
		if (((t_word *)lst->content)->type == D_INPUT)
			priority = PRIORITY_INPUT;
		else if (((t_word *)lst->content)->type == D_HEREDOC)
			priority = PRIORITY_HERE_DOC;
		lst = lst->next;
	}
	return (priority);
}

int	ft_open_new(void)
{
	int	status;
	int	fd;

	status = SUCCESS; 
	fd = open("/dev/pts/0", O_WRONLY);
	if (fd == FD_FAIL_OPEN || fd != STDIN)
	{
		status = FAIL;
		close(fd);
	}
	return (status);
}

int	ft_exec_here_doc(t_data *data)
{
	int	status;
	int	fd_tmp;

	status = BAD_PARAMETER;
	if (data)
	{
		status = DUP_FAIL_STATUS;
		fd_tmp = dup(STDIN);
		if (fd_tmp != EXEC_DUP_FAIL)
		{
			status = ft_signal_heredoc();
			if (status == SIGNAL_HANDLING)
				status = ft_exec_here_doc_func(data);
			if (g_signal_handle == SIGINT_SIGNAL)
			{
				if (ft_open_new() != SUCCESS)
					status = FD_FAIL_STATUS;
				if (dup2(fd_tmp, 0) == EXEC_DUP_FAIL)
					status = DUP_FAIL_STATUS;
			}
			close(fd_tmp);
		}
	}
	return (status);
}
