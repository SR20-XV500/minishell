/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:44:12 by tlassere          #+#    #+#             */
/*   Updated: 2025/05/11 13:53:41 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_words_clear(t_list **begin)
{
	ft_lstclear(begin, &ft_word_free);
}

static t_word	*ft_word_make(char *str, int type)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (word)
	{
		word->type = type;
		word->word = str;
	}
	return (word);
}

t_list	*ft_word_lst_make_join(char *str, int type)
{
	t_list	*lst;
	t_word	*word;

	lst = NULL;
	word = ft_word_make(str, type);
	if (word)
	{
		lst = ft_lstnew(word);
		if (lst == NULL)
			free(word);
	}
	return (lst);
}
