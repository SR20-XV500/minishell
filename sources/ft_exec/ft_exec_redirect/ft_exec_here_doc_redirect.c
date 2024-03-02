/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_here_doc_redirect.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 00:57:52 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/01 15:36:41 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_here_doc_get_pos(t_data *data, t_list *lst_start)
{
	int		pos;
	int		buffer;
	int		is_view;
	t_list	*lst;

	pos = 0;
	buffer = FAIL;
	is_view = FAIL;
	lst = data->words;
	while (lst && lst->content)
	{
		if (lst == lst_start)
			is_view = SUCCESS;
		if (((t_word *)lst->content)->type == D_HEREDOC
			&& buffer == SUCCESS && is_view == FAIL)
		{
			buffer = FAIL;
			pos++;
		}
		else if (((t_word *)lst->content)->type == D_PIPE && is_view == FAIL)
			buffer = SUCCESS;
		lst = lst->next;
	}
	return (pos);
}

static int	ft_write_pipe(int fd, t_list *here_doc)
{
	int		status;
	char	*str;
	char	new_line;

	status = SUCCESS;
	new_line = '\n';
	while (status == SUCCESS && here_doc
		&& ((t_word *)here_doc->content)->type != HER_EOF)
	{
		str = ((t_word *)here_doc->content)->word;
		if ((str && write(fd, str, ft_strlen(str)) == -1)
			|| write(fd, &new_line, 1) == -1)
			status = ERR_WRITE_FAIL;
		here_doc = here_doc->next;
	}
	return (status);
}

int	ft_exec_here_doc_redirect(t_data *data, t_list *lst_start)
{
	int	status;
	int	std[2];

	status = BAD_PARAMETER;
	if (data && lst_start)
	{
		status = ERR_PIPE_FAIL;
		if (pipe(std) == SUCCESS)
		{
			status = ft_write_pipe(std[STDOUT],
					data->here_doc[ft_here_doc_get_pos(data, lst_start)]);
			if (status == ERR_WRITE_FAIL
				&& (close(std[STDIN]) == -1 || close(std[STDOUT]) == -1))
				status = ERR_CLOSE_FAIL;
			else
			{
				if (close(std[STDOUT]) == -1)
					status = ERR_CLOSE_FAIL;
				if (data->input_fd > 2)
					close(data->input_fd);
				data->input_fd = std[STDIN];
			}
		}
	}
	return (status);
}
