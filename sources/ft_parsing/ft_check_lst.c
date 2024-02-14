/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:16:24 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/13 01:55:15 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_operator(t_list *prev, t_list *lst_cur, int *status)
{
	t_list	*next;

	if (lst_cur)
	{
		next = lst_cur->next;
		if (prev == NULL && ((t_word *)lst_cur->content)->type == D_PIPE)
		{
			*status = PARSER_NEAR_PIPE
				| (((t_word *)lst_cur->content)->type << 5);
		}
		else if ((next == NULL || ((t_word *)next->content)->type > D_NOT_SET)
			&& ((t_word *)lst_cur->content)->type > D_NOT_SET)
		{
			*status = PARSER_ERR_OP_NEWLINE;
			if (next == NULL)
				*status |= D_NEW_LINE << 5;
			else
				*status |= ((t_word *)next->content)->type << 5;
		}
		else
			ft_check_operator(lst_cur, next, status);
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

// TODO: change exit status code 

int	ft_check_lst(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = SUCCESS;
		ft_check_operator(NULL, data->words, &status);
		if (status != SUCCESS)
		{
			ft_check_error(status);
			status = FAIL;
			data->env->exit_status = 2;
		}
	}
	return (status);
}