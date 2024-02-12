/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:16:24 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/12 22:59:42 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_operator(t_list *prev, t_list *lst_cur, int *status)
{
	t_list	*next;

	if (lst_cur)
	{
		next = lst_cur->next;
		if (next == NULL && ((t_word *)lst_cur->content)->type > D_NOT_SET)
		{
			*status = PARSER_ERR_OP_NEWLINE
				| (((t_word *)lst_cur->content)->type << 5);
		}
		else if (prev == NULL && ((t_word *)lst_cur->content)->type == D_PIPE)
		{
			*status = PARSER_NEAR_PIPE
				| (((t_word *)lst_cur->content)->type << 5);
		}
		else
			ft_check_operator(lst_cur, next, status);
	}
}

static void	ft_check_error(int err)
{
	char	*print;

	print = NULL;
	if (err & PARSER_ERR_OP_NEWLINE)
	{
		if ((err >> 5) == D_PIPE)
			print = "|";
	}
	else if (err & PARSER_NEAR_PIPE)
	{
	}
	ft_printf("%s\n", print);
}

int	ft_check_lst(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = SUCCESS;
		ft_check_operator(NULL, data->words, &status);
		if (status == SUCCESS)
		{
		}
		else
			ft_check_error(status);
	}
	return (status);
}
