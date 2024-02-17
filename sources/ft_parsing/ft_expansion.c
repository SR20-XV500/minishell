/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:53:49 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/17 12:41:56 by tlassere         ###   ########.fr       */
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

// cet fonction pue la merde elle ne fait pas se qu'il faut, a refaire

//int	ft_expansion_str(const char *str, char **new_str)
//{
//	int		status;
//	char	*curent_card;

//	status = BAD_PARAMETER;
//	curent_card = NULL;
//	if (str && new_str)
//	{
//		status = PARSER_EXPANSION_VAR_NO_CHANGE;
//		if (ft_strchr(str, '$'))
//			curent_card = ft_expansion_get_str(str);
//		if (ft_strchr(str, '$') || curent_card)
//		{
//			if (curent_card && (ft_strlen(str) != ft_strlen(curent_card)
//				|| ft_strcmp_s2(curent_card, str) != CMP_EGAL))
//			{
//				*new_str = curent_card;
//				status = PARSER_EXPANSION_VAR_CHANGE; 
//			}
//			else
//				free(curent_card);
//		}
//		else
//			status = MALLOC_FAIL;
//	}
//	return (status);
//}

//static int	ft_expansion_replace_word_content(t_word *word)
//{
//	int		status;
//	char	*new_str;

//	status = BAD_PARAMETER;
//	new_str = NULL;
//	if (word && word->word)
//	{
//		if (word->type == D_NOT_SET)
//		{
//			status = ft_expansion_str(word->word, &new_str);
//		}
//		if (status != MALLOC_FAIL)
//			status = SUCCESS;
//	}
//	return (status);
//}

//static int	ft_expansion_replace_word(t_list *lst)
//{
//	int	status;

//	status = BAD_PARAMETER;
//	if (lst)
//	{
//		status = SUCCESS;
//		while (lst && status == SUCCESS)
//		{
//			status = ft_expansion_replace_word_content(lst->content);
//			lst = lst->next;
//		}
//	}
//	return (status);
//}

int	ft_expansion(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		//status = ft_expansion_replace_word(data->words);
	}
	return (status);
}
