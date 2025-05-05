/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:53:49 by tlassere          #+#    #+#             */
/*   Updated: 2025/05/06 01:39:32 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expansion_is_word(const char *str)
{
	if (*str == '$' && (ft_isalpha(*(str + 1)) || *(str + 1) == '_'
		|| *(str + 1) == '?'))
		return (TRUE);
	return (FALSE);
}

static void ft_remove_caracter(char *str)
{
	memmove(str, str + 1, strlen(str));	
}

static int ft_quote_using(char *str, int *inquote)
{
	if (*inquote == TRUE)
	{
		*inquote = FALSE;
		ft_remove_caracter(str);
		return (TRUE);
	}
	if (*inquote == FALSE && ft_strchr(str + 1, '"'))
	{
		*inquote = TRUE;
		ft_remove_caracter(str);
		return (TRUE);
	}
	return (FALSE);
}

static int skip_simple_quote(char **str)
{
	char	*next;

	if (**str == '\'')
	{
		next = ft_strchr(*str + 1, '\'');
		if (next)
		{
			next--;
			ft_remove_caracter(*str);
			ft_remove_caracter(next);
			*str = next;
			return (TRUE);
		}
	}
	return (FALSE);
}

static int ft_expend_word(t_data *data, t_list *lst)
{
	t_word	*word;	
	char *str;
	int inquote;

	word = lst->content;
	str = word->word;
	inquote = FALSE;
	while (*str)
	{
		if ((*str != '"' || ft_quote_using(str, &inquote) == FALSE) && ( inquote == TRUE || skip_simple_quote(&str) == FALSE))
		{
			
			str++;
		}
	}
	
	ft_printf("str: %s\ntype: %d\n", word->word, word->type);
	(void)data;
	return (SUCCESS);
}

static int ft_while_data(t_data *data)
{
	int status;
	t_list *current;
	t_list *next;

	status = SUCCESS;
	current = data->words;
	while (current && status == SUCCESS)
	{
		next = current->next;
		status = ft_expend_word(data, current);
		current = next;
	}
	return (status);
}

int	ft_expansion(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = ft_while_data(data);
	}
	return (status);
}
