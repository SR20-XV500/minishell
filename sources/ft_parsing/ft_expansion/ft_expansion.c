/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:53:49 by tlassere          #+#    #+#             */
/*   Updated: 2025/05/11 14:08:11 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_quote_using(char *str, int *inquote)
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

static int	skip_simple_quote(char **str)
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

static int	ft_expend_word(t_data *data, t_list *lst)
{
	t_word	*word;	
	char	*str;
	int		inquote;

	word = lst->content;
	str = word->word;
	inquote = FALSE;
	while (str && *str)
	{
		if ((*str != '"' || ft_quote_using(str, &inquote) == FALSE)
			&& (inquote == TRUE || skip_simple_quote(&str) == FALSE))
		{
			if (ft_expansion_is_word(str))
				str = ft_expend_teraform(data, &lst, str, inquote);
			else
				str++;
		}
	}
	return (SUCCESS);
}

static int	ft_while_data(t_data *data)
{
	int		status;
	t_list	*current;
	t_list	*next;
	int		type;

	status = SUCCESS;
	current = data->words;
	while (current && status == SUCCESS)
	{
		next = current->next;
		type = ((t_word *)current->content)->type;
		if (type == D_NOT_SET || type == TY_PATH)
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
		// TODO remove NULL node word
	}
	return (status);
}
