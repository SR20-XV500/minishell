/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_here_doc_func.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:27:04 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/08 16:41:40 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_here_doc(t_data *data)
{
	int		count;
	int		buffer;
	t_list	*lst;

	count = 0;
	buffer = SUCCESS;
	if (data)
	{
		lst = data->words;
		count++;
		while (lst && lst->content)
		{
			if (((t_word *)lst->content)->type == D_HEREDOC
				&& buffer == SUCCESS)
			{
				buffer = FAIL;
				count++;
			}
			else if (((t_word *)lst->content)->type == D_PIPE)
				buffer = SUCCESS;
			lst = lst->next;
		}
	}
	return (count);
}

static int	ft_make_here_doc(t_data *data)
{
	int	status;
	int	len;

	status = BAD_PARAMETER;
	if (data)
	{
		status = SUCCESS;
		len = ft_count_here_doc(data);
		if (len > 1)
		{
			data->here_doc = malloc(sizeof(t_list *) * len);
			if (data->here_doc)
				ft_bzero(data->here_doc, sizeof(t_list *) * len);
			else
				status = MALLOC_FAIL;
		}
	}
	return (status);
}

static int	ft_here_doc_add_content(t_data *data)
{
	int		status;
	t_list	*current;
	t_list	**buffer;

	status = SUCCESS;
	current = data->words;
	buffer = data->here_doc;
	while (status == SUCCESS && current && g_signal_handle != SIGINT_SIGNAL)
	{
		if (((t_word *)current->content)->type == TY_DELIM_HEREDOC)
		{
			ft_lstclear(buffer, &ft_word_free);
			*buffer = ft_here_doc_delimiter(data,
					((t_word *)current->content)->word);
			if (*buffer == NULL)
				status = MALLOC_FAIL;
		}
		if (*buffer && ((t_word *)current->content)->type == D_PIPE
			&& status == SUCCESS && g_signal_handle != SIGINT_SIGNAL)
			buffer++;
		current = current->next;
	}
	if (status == MALLOC_FAIL || g_signal_handle == SIGINT_SIGNAL)
		ft_free_here_doc(&data->here_doc);
	return (status);
}


int	ft_exec_here_doc_func(t_data *data)
{
	int	status;

	status = ft_make_here_doc(data);
	if (status == SUCCESS && data->here_doc)
		status = ft_here_doc_add_content(data);
	return (status);
}
