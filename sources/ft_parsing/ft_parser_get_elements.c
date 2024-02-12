/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_get_elements.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:17:28 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/12 22:59:17 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parser_add_delimiter(t_data *data, const char *str, size_t *i)
{
	int	status;

	status = D_NOT_SET;
	if (ft_strcmp_s2(str, ">>") == CMP_EGAL)
	{
		status = ft_word_add(data, ">>", D_OUTPUT_APPEND);
		(*i)++;
	}
	else if (ft_strcmp_s2(str, "<<") == CMP_EGAL)
	{
		status = ft_word_add(data, "<<", D_HEREDOC);
		(*i)++;
	}
	else if (ft_strcmp_s2(str, "|") == CMP_EGAL)
		status = ft_word_add(data, "|", D_PIPE);
	else if (ft_strcmp_s2(str, "<") == CMP_EGAL)
		status = ft_word_add(data, "<", D_INPUT);
	else if (ft_strcmp_s2(str, ">") == CMP_EGAL)
		status = ft_word_add(data, ">", D_OUTPUT_NEW);
	if (status == SUCCESS)
		(*i)++;
	return (status);
}

static size_t	ft_parser_get_index(const char *str)
{
	char	*ptr_buffer;
	size_t	index;

	index = 0;
	while (str && *(str + index)
		&& ft_strchr("|<> \t\v\f", *(str + index)) == NULL)
	{
		ptr_buffer = NULL;
		if (str[index] == '\"')
		{
			ptr_buffer = ft_strchr(str + index + 1, '\"');
			if (ptr_buffer)
				index += ptr_buffer - (str + index);
		}
		else if (str[index] == '\'')
		{
			ptr_buffer = ft_strchr(str + index + 1, '\'');
			if (ptr_buffer)
				index += ptr_buffer - (str + index);
		}
		index++;
	}
	return (index);
}

static int	ft_parser_get_word(char **get_word, const char *str, size_t *i)
{
	size_t	sub_index;
	int		status;

	sub_index = 0;
	status = BAD_PARAMETER;
	if (get_word && str && i)
	{
		status = PARSER_NO_WORD;
		sub_index = ft_parser_get_index(str);
		if (sub_index > 0)
		{
			status = PARSER_WORD;
			*get_word = ft_substr(str, 0, sub_index);
			if (*get_word == NULL)
				status = MALLOC_FAIL;
		}
		*i += sub_index;
	}	
	return (status);
}

static int	ft_parser_put_word(t_data *data, const char *str, size_t *i)
{
	char	*word;
	int		status;

	status = BAD_PARAMETER;
	word = NULL;
	if (data && str && i && *str)
	{
		status = ft_parser_get_word(&word, str, i);
		if (status == PARSER_WORD)
		{
			status = ft_word_add(data, word, D_NOT_SET);
			free(word);
		}
	}
	return (status);
}

int	ft_parser_use_line(t_data *data, const char *str)
{
	int		ret;
	int		buffer;
	size_t	i;

	ret = SUCCESS;
	i = 0;
	while (str[i] && ret == SUCCESS)
	{
		while (str[i] && ft_strchr(" \t\v\f", str[i]))
			i++;
		buffer = ft_parser_add_delimiter(data, str + i, &i);
		if (buffer != MALLOC_FAIL)
			buffer = ft_parser_put_word(data, str + i, &i);
		if (buffer == MALLOC_FAIL)
			ret = MALLOC_FAIL;
	}
	return (ret);
}
