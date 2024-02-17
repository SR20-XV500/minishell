/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:53:49 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/17 13:09:16 by tlassere         ###   ########.fr       */
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

int	ft_expansion_str(t_data *data, const char *str, char **new_str)
{
	int	status;

	status = BAD_PARAMETER;
	if (str && new_str)
	{
		status = PARSER_EXPANSION_VAR_NO_CHANGE;
		if (ft_strchr(str, '$'))
		{
			status = PARSER_EXPANSION_VAR_CHANGE;
			*new_str = ft_expansion_get_str(data, str);
		}
	}
	return (status);
}

static int	ft_expansion_replace_word_content(t_data *data, t_word *word)
{
	int		status;
	char	*new_str;

	status = BAD_PARAMETER;
	new_str = NULL;
	if (word && word->word)
	{
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
	return (status);
}

static int	ft_expansion_replace_word(t_data *data)
{
	int		status;
	t_list	*lst;

	status = BAD_PARAMETER;
	lst = data->words;
	if (lst)
	{
		status = SUCCESS;
		while (lst && status == SUCCESS)
		{
			status = ft_expansion_replace_word_content(data, lst->content);
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
		status = ft_expansion_replace_word(data);
	}
	return (status);
}
