/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_here_doc_delimitor.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:04:49 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/28 21:05:50 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_expantion_get_while_here_doc(t_data *data,
	const char *str, size_t *i, char **buffer)
{
	int	status;

	if (ft_expansion_is_word(str + *i) == SUCCESS)
		status = ft_expansion_join_var(data, str + *i, buffer, i);
	else
		status = ft_expansion_add_car(*buffer, str[*i], buffer);
	return (status);
}

static t_list	*ft_here_doc_get_content(const char *delim, size_t *line_count)
{
	char	*line;
	int		status;
	t_list	*lst;

	line = readline("> ");
	lst = NULL;
	status = SUCCESS;
	while (line && ft_strncmp(delim, line, ft_strlen(delim) + 1) != CMP_EGAL
		&& status == SUCCESS)
	{
		(*line_count)++;
		status = ft_word_add_lst(&lst, line, HER_STR);
		if (status == SUCCESS)
			free(line);
		if (status == SUCCESS)
			line = readline("> ");
	}
	if (status == SUCCESS)
		status = ft_word_add_lst(&lst, line, HER_EOF);
	if (status != SUCCESS)
		ft_lstclear(&lst, &ft_word_free);
	if (line != NULL)
		(*line_count)++;
	free(line);
	return (lst);
}

static void	ft_here_doc_expansion(t_data *data, t_list **lst)
{
	char	*buffer;
	t_list	*current;
	t_word	*word;

	buffer = NULL;
	current = *lst;
	while (current)
	{
		word = current->content;
		if (word->type == HER_STR && ft_strchr(word->word, '$'))
		{
			buffer = ft_expansion_get_str_func(data, word->word,
					&ft_expantion_get_while_here_doc);
			free(word->word);
			word->word = buffer;
		}
		current = current->next;
	}
}

t_list	*ft_here_doc_delimitor(t_data *data, char *str)
{
	int		expand;
	t_list	*lst;
	size_t	buffer;
	size_t	line_count;

	expand = SUCCESS;
	lst = NULL;
	line_count = 0;
	if (str)
	{
		buffer = ft_strlen(str);
		ft_quotes_remove(str);
		if (buffer != ft_strlen(str))
			expand = FAIL;
		lst = ft_here_doc_get_content(str, &line_count);
		if (lst && expand == SUCCESS)
			ft_here_doc_expansion(data, &lst);
		if (lst && ((t_word *)ft_lstlast(lst)->content)->word == NULL
			&& (ft_fprintf(STDERR, ERR_HERE_DOC, (int)data->line_count) < 0
				|| ft_fprintf(STDERR, ERR_HERE_DOC_2, str) == -1))
			ft_lstclear(&lst, &ft_word_free);
		data->line_count += line_count;
	}
	return (lst);
}
