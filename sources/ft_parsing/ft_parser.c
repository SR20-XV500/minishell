/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:14:15 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/12 01:43:31 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parser_add_delimitor(t_data *data, const char *str, size_t *i)
{
	int	status;

	status = D_NOT_SET;
	if (ft_strcmp_s2(str, ">>") == CMP_EGAL)
	{
		status = ft_word_add(data, ">>", D_OUTPUT_APEND);
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
		status = ft_word_add(data, "<", D_INTPUT);
	else if (ft_strcmp_s2(str, ">") == CMP_EGAL)
		status = ft_word_add(data, ">", D_OUTPUT);
	else if (ft_strcmp_s2(str, "\"") == CMP_EGAL
		|| ft_strcmp_s2(str, "\'") == CMP_EGAL)
		status = D_QUOTE;
	if (status != MALLOC_FAIL && status != D_QUOTE && status != D_NOT_SET)
		(*i)++;
	return (status);
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
		while (*(str + sub_index)
			&& ft_strchr("|<> \t\v\f\"\'", *(str + sub_index)) == NULL)
			sub_index++;
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
	if (data && str && i)
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

// TODO: quote

static int	ft_parser_use_line(t_data *data, const char *str)
{
	int		ret;
	int		buffer;
	size_t	i;

	ret = SUCCESS;
	i = 0;
	while (str[i] && ret == SUCCESS)
	{
		while (ft_strchr(" \t\v\f", str[i]))
			i++;
		buffer = ft_parser_add_delimitor(data, str + i, &i);
		if (buffer != MALLOC_FAIL)
			buffer = ft_parser_put_word(data, str + i, &i);
		if (buffer == MALLOC_FAIL)
			ret = MALLOC_FAIL;
	}
	return (ret);
}

int	ft_parser(t_data *data, const char *str)
{
	int	ret;

	ret = BAD_PARAMETER;
	if (data && str)
	{
		ret = ft_parser_use_line(data, str);
	}
	return (ret);
}
