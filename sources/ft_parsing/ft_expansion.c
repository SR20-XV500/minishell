/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:53:49 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/18 20:19:53 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expansion_is_word(const char *str)
{
	int	status;

	status = BAD_PARAMETER;
	if (str)
	{
		status = FAIL;
		if (*str == '$' && (ft_isalpha(*(str + 1))
				|| *(str + 1) == '_' || *(str + 1) == '?'))
			status = SUCCESS;
	}
	return (status);
}

static int	ft_expansion_replace_word_content(t_data *data,
	t_list **lst, t_list *last)
{
	int		status;
	char	*new_str;
	t_word	*word;

	status = BAD_PARAMETER;
	new_str = NULL;
	if (lst && *lst && (*lst)->content
		&& ((t_word *)(*lst)->content)->word && data)
	{
		word = (*lst)->content;
		status = SUCCESS;
		if (word->type == D_NOT_SET)
		{
			status = ft_expansion_str(data, word->word, &new_str);
			if (status == PARSER_EXPANSION_VAR_CHANGE)
			{
				free(word->word);
				word->word = new_str;
			}
		}
		if (status != MALLOC_FAIL)
			status = SUCCESS;
	}
	(void)last;
	return (status);
}

static int	ft_expansion_put_lst(t_data *data,
	int (*f)(t_data *, t_list **, t_list *))
{
	int		status;
	t_list	*lst;
	t_list	*last;

	status = BAD_PARAMETER;
	lst = data->words;
	last = NULL;
	if (lst)
	{
		status = SUCCESS;
		while (lst && status == SUCCESS)
		{
			status = (*f)(data, &lst, last);
			last = lst;
			lst = lst->next;
		}
	}
	return (status);
}

int	ft_expansion(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = ft_expansion_put_lst(data, &ft_expansion_replace_word_content);
		if (status == SUCCESS)
			status = ft_expansion_put_lst(data, &ft_expansion_split_node);
	}
	return (status);
}
