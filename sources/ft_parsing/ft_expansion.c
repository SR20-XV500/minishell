/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:53:49 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/16 19:17:05 by tlassere         ###   ########.fr       */
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

int	ft_expansion_str(const char *str, char **new_str)
{
	int		status;
	char	*curent_card;

	status = BAD_PARAMETER;
	curent_card = (char *)str;
	if (str && new_str)
	{
		status = PARSER_EXPANSION_VAR_NO_CHANGE;
		curent_card = ft_strchr(curent_card, '$');
		while (curent_card)
		{
			if (ft_expansion_is_word(curent_card) == SUCCESS)
			{

				status = PARSER_EXPANSION_VAR_CHANGE;
			}
			curent_card++;
			while (*curent_card == '$')
				curent_card++;
			curent_card = ft_strchr(curent_card, '$');
		}
	}
	return (status);
}

static int	ft_expansion_replace_word_content(t_word *word)
{
	int		status;
	char	*new_str;

	status = BAD_PARAMETER;
	new_str = NULL;
	if (word && word->word)
	{
		if (word->type == D_NOT_SET)
		{
			status = ft_expansion_str(word->word, &new_str);
		}
		if (status != MALLOC_FAIL)
			status = SUCCESS;
	}
	return (status);
}

static int	ft_expansion_replace_word(t_list *lst)
{
	int	status;

	status = BAD_PARAMETER;
	if (lst)
	{
		status = SUCCESS;
		while (lst && status == SUCCESS)
		{
			status = ft_expansion_replace_word_content(lst->content);
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
		status = ft_expansion_replace_word(data->words);
	}
	return (status);
}
