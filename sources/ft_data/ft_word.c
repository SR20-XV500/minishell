/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:51:18 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/27 18:11:32 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_word	*ft_word_make(const char *str, int type)
{
	t_word	*word;
	char	*dump;

	word = NULL;
	dump = NULL;
	if (str)
		dump = ft_strdup(str);
	if (dump || (str == NULL && dump == NULL))
	{
		word = malloc(sizeof(t_word));
		if (word)
		{
			word->type = type;
			word->word = dump;
		}
		else if (str)
			free(dump);
	}
	return (word);
}

t_list	*ft_word_lst_make(const char *str, int type)
{
	t_list	*lst;
	t_word	*word;

	lst = NULL;
	word = ft_word_make(str, type);
	if (word)
	{
		lst = ft_lstnew(word);
		if (lst == NULL)
			ft_word_free(word);
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
	int		ret;

	ret = BAD_PARAMETER;
	if (data && str)
		ret = ft_word_add_lst(&data->words, str, type);
	return (ret);
}