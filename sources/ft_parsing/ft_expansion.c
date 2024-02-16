/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:53:49 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/16 19:42:24 by tlassere         ###   ########.fr       */
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

char	*ft_expansion_get_str(const char *str)
{
	char	*new_str;
	size_t	i;

	new_str = NULL;
	i = 0;
	if (str)
	{
		
	}
	return (new_str);
}

int	ft_expansion_str(const char *str, char **new_str)
{
	int		status;
	char	*curent_card;

	status = BAD_PARAMETER;
	if (str && new_str)
	{
		status = MALLOC_FAIL;
		curent_card = ft_expansion_get_str(str);
		if (curent_card == NULL)
		{
			status = PARSER_EXPANSION_VAR_NO_CHANGE;
			if (curent_card && (ft_strlen(str) != ft_strlen(curent_card)
				|| ft_strcmp_s2(curent_card, str) != CMP_EGAL))
			{
				*new_str = curent_card;
				status = PARSER_EXPANSION_VAR_CHANGE; 
			}
			else
				free(curent_card);
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
