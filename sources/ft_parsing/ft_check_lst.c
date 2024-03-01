/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:16:24 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/01 16:44:09 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_operator(t_word *prev, t_word *lst_cur,
	t_word *next, int *status)
{
	if (lst_cur)
	{
		if (prev == NULL && lst_cur->type == D_PIPE)
		{
			*status = PARSER_NEAR_PIPE
				| (lst_cur->type << 5);
		}
		else if ((next == NULL || next->type > D_NOT_SET)
			&& lst_cur->type > D_NOT_SET)
		{
			*status = PARSER_ERR_OP_NEWLINE;
			if (next == NULL)
				*status |= D_NEW_LINE << 5;
			else if (lst_cur->type != D_PIPE)
				*status |= next->type << 5;
			else
				*status = SUCCESS;
		}
	}
}

static void	ft_check_error(int err)
{
	char	*print;

	print = NULL;
	if (err & PARSER_ERR_OP_NEWLINE || err & PARSER_NEAR_PIPE)
	{
		if ((err >> 5) == D_PIPE)
			print = "|";
		else if ((err >> 5) == D_INPUT)
			print = "<";
		else if ((err >> 5) == D_OUTPUT_APPEND)
			print = ">>";
		else if ((err >> 5) == D_OUTPUT_NEW)
			print = ">";
		else if ((err >> 5) == D_HEREDOC)
			print = "<<";
		else
			print = "newline";
		ft_fprintf(STDERR, "minishell: syntax error near unexpected token ");
		ft_fprintf(STDERR, "`%s'\n", print);
	}
}

static void	ft_check_args(t_data *data, int *status)
{
	t_list	*prev;
	t_list	*next;
	t_list	*current;
	t_word	*w_prev;
	t_word	*w_next;

	current = data->words;
	prev = NULL;
	while (current && *status == SUCCESS)
	{
		next = current->next;
		w_prev = NULL;
		w_next = NULL;
		if (next)
			w_next = next->content;
		if (prev)
			w_prev = prev->content;
		ft_check_operator(w_prev, current->content,
			w_next, status);
		prev = current;
		current = current->next;
	}
}

int	ft_check_lst(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = SUCCESS;
		ft_check_args(data, &status);
		if (status != SUCCESS)
		{
			ft_check_error(status);
			status = FAIL;
			data->env->exit_status = 2;
		}
	}
	return (status);
}
