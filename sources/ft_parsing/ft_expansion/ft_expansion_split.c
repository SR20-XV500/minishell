/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:39:20 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/04 13:11:06 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_expansion_get_word(char **str)
{
	char	*new_str;
	char	*end;

	end = *str;
	while (*end && ft_strchr(" \t\v\f\r\n", *end) == NULL)
	{
		if (*end == '\"' && ft_strchr(end + 1, '\"'))
			end = ft_strchr(end + 1, '\"');
		if (*end == '\'' && ft_strchr(end + 1, '\''))
			end = ft_strchr(end + 1, '\'');
		end++;
	}
	new_str = ft_substr(*str, 0, end - *str);
	*str = end;
	return (new_str);
}

static t_list	*ft_expansion_get_current_node(char **str)
{
	char	*word;
	t_list	*node;

	word = NULL;
	node = NULL;
	if (str && *str)
	{
		while (**str && ft_strchr(" \t\v\f\r\n", **str))
			(*str)++;
		if (**str)
		{
			word = ft_expansion_get_word(str);
			if (word)
				node = ft_word_lst_make(word, D_NOT_SET);
		}
		else
			node = ft_word_lst_make(word, D_NOT_SET);
		free(word);
	}
	return (node);
}

t_list	*ft_expansion_split_node_content(const char *str)
{
	t_list	*lst_begin;
	t_list	*last;
	char	*buffer;

	lst_begin = NULL;
	last = NULL;
	buffer = (char *)str;
	if (str)
	{
		while (buffer && *buffer)
		{
			last = ft_expansion_get_current_node(&buffer);
			if (last == NULL)
			{
				ft_lstclear(&lst_begin, &ft_word_free);
				buffer = NULL;
			}
			else
				ft_lstadd_back(&lst_begin, last);
		}
	}
	return (lst_begin);
}

int	ft_expansion_is_multi_arg(const char *str)
{
	int		status;
	char	*cpy_ptr;

	status = BAD_PARAMETER;
	cpy_ptr = (char *)str;
	if (str)
	{
		status = FAIL;
		while (*cpy_ptr && status == FAIL)
		{
			if (*cpy_ptr == '\"' && ft_strchr(cpy_ptr + 1, '\"'))
				cpy_ptr = ft_strchr(cpy_ptr + 1, '\"');
			if (*cpy_ptr == '\'' && ft_strchr(cpy_ptr + 1, '\''))
				cpy_ptr = ft_strchr(cpy_ptr + 1, '\'');
			if (*cpy_ptr && ft_strchr(" \t\v\r\n\f", *cpy_ptr))
				status = SUCCESS;
			cpy_ptr++;
		}
	}
	return (status);
}
