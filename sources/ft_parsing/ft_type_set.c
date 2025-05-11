/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:29:20 by tlassere          #+#    #+#             */
/*   Updated: 2025/05/11 20:58:54 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_type_node(t_list *cur_lst)
{
	t_list	*new_node;

	new_node = ft_word_lst_make(((t_word *)cur_lst->content)->word, TY_PATH);
	if (new_node == NULL)
		return (MALLOC_FAIL);
	new_node->next = cur_lst->next;
	cur_lst->next = new_node;
	return (SUCCESS);
}

static int	ft_type_path(t_list *cur_lst)
{
	t_word	*cur_word;
	int		target;

	cur_word = NULL;
	target = TY_NOT_SET;
	while (cur_lst)
	{
		cur_word = cur_lst->content;
		if (target != TY_NOT_SET)
		{
			cur_word->type = target;
			if (target == TY_NOEXPENDED && ft_type_node(cur_lst) != SUCCESS)
				return (MALLOC_FAIL);
			target = TY_NOT_SET;
		}
		else if (cur_word->type == D_INPUT || cur_word->type == D_OUTPUT_APPEND
			|| cur_word->type == D_OUTPUT_NEW)
			target = TY_NOEXPENDED;
		else if (cur_word->type == D_HEREDOC)
			target = TY_DELIM_HEREDOC;
		cur_lst = cur_lst->next;
	}
	return (SUCCESS);
}

static void	ft_type_cmd(t_list *lst)
{
	t_list	*cur_lst;
	t_word	*cur_word;
	int		target;

	cur_lst = lst;
	cur_word = NULL;
	target = TY_CMD;
	while (cur_lst)
	{
		cur_word = cur_lst->content;
		if (cur_word->type == D_NOT_SET)
		{
			cur_word->type = target;
			target = TY_ARG;
		}
		else if (cur_word->type == D_PIPE)
			target = TY_CMD;
		cur_lst = cur_lst->next;
	}
}

int	ft_type_set_path(t_data *data)
{
	return (ft_type_path(data->words));
}

int	ft_type_set_cmd(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = SUCCESS;
		ft_type_cmd(data->words);
	}
	return (status);
}
