/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:38:04 by tlassere          #+#    #+#             */
/*   Updated: 2025/05/11 14:12:02 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_expand_left_node(t_list **begin, t_teraform *teraform, int type)
{
	char	*buffer;

	if (teraform->left)
	{
		if (teraform->sp[0] && teraform->ljoin)
			buffer = ft_strjoin(teraform->left, teraform->sp[0]);
		else
			buffer = ft_strdup(teraform->left);
		return (join_create_set_node(begin, buffer, type));
	}
	return (SUCCESS);
}

int	join_expand_right_node(t_list **begin, t_teraform *teraform,
	int type, char **newpos)
{
	char	*buffer;
	t_word	*last;
	size_t	len;

	if (teraform->right)
	{
		if (teraform->rjoin && *begin)
		{
			last = ft_lstlast(*begin)->content;
			len = ft_strlen(last->word);
			buffer = ft_strjoin(last->word, teraform->right);
			if (buffer == NULL)
				return (FAIL);
			free(last->word);
			last->word = buffer;
			*newpos = buffer + len;
		}
		else
		{
			if (join_create_set_node(begin, ft_strdup(teraform->right), type))
				return (FAIL);
			*newpos = ((t_word *)ft_lstlast(*begin)->content)->word;
		}
	}
	return (SUCCESS);
}

int	join_middle(t_list **begin, t_teraform *teraform, int type)
{
	size_t	i;

	i = 0;
	if (teraform->sp[i])
	{
		if (teraform->left && teraform->ljoin)
			i++;
		while (teraform->sp[i])
		{
			if (join_create_set_node(begin,
					ft_strdup(teraform->sp[i]), type) == FAIL)
				return (FAIL);
			i++;
		}
	}
	return (SUCCESS);
}

char	*join_nodes(t_list **lst, t_list *newlst, char *newpos)
{
	t_word	*buffer;
	t_list	*last;

	if (newlst == NULL)
	{
		buffer = (*lst)->content;
		free(buffer->word);
		buffer->word = NULL;
		return (NULL);
	}
	last = ft_lstlast(newlst);
	ft_word_free((*lst)->content);
	(*lst)->content = newlst->content;
	if (last != newlst)
	{
		last->next = (*lst)->next;
		(*lst)->next = newlst->next;
		*lst = last;
	}
	free(newlst);
	return (newpos);
}

char	*join_expand(t_list **lst, t_teraform *teraform, char *str)
{
	t_list	*newlst;
	int		type;
	char	*newpos;

	newlst = NULL;
	type = ((t_word *)(*lst)->content)->type;
	newpos = NULL;
	if (join_expand_left_node(&newlst, teraform, type) == FAIL)
		return (str);
	if (join_middle(&newlst, teraform, type) == FAIL)
		return (ft_words_clear(&newlst), str);
	if (join_expand_right_node(&newlst, teraform, type, &newpos) == FAIL)
		return (ft_words_clear(&newlst), str);
	if (newlst == NULL)
		return (NULL);
	return (join_nodes(lst, newlst, newpos));
}
