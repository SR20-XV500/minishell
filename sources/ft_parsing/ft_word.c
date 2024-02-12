/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:51:18 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/11 17:33:02 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_word	*ft_word_make(const char *str, int type)
{
	t_word	*word;
	char	*dump;

	word = NULL;
	if (str)
	{
		dump = ft_strdup(str);
		if (dump)
		{
			word = malloc(sizeof(t_word));
			if (word)
			{
				word->type = type;
				word->word = dump;
			}
			else
				free(dump);
		}
	}
	return (word);
}

t_list	*ft_word_lst_make(const char *str, int type)
{
	t_list	*lst;
	t_word	*word;

	lst = NULL;
	if (str)
	{
		word = ft_word_make(str, type);
		if (word)
		{
			lst = ft_lstnew(word);
			if (lst == NULL)
				ft_word_free(word);
		}
	}
	return (lst);
}

void	ft_word_free(void *data)
{
	t_word	*word;

	if (data)
	{
		word = data;
		free(word->word);
		free(word);
	}
}

void	ft_word_lst_clear(t_data *data)
{
	ft_lstclear(&data->words, &ft_word_free);
}

int	ft_word_add(t_data *data, const char *str, int type)
{
	t_list	*lst;
	int		ret;

	ret = BAD_PARAMETER;
	if (data && str)
	{
		ret = MALLOC_FAIL;
		lst = ft_word_lst_make(str, type);
		if (lst)
		{
			ret = SUCCESS;
			ft_lstadd_back(&data->words, lst);
		}
	}
	return (ret);
}