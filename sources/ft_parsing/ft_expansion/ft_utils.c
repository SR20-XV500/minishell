/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:33:24 by tlassere          #+#    #+#             */
/*   Updated: 2025/05/11 13:36:53 by tlassere         ###   ########.fr       */
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

void ft_remove_caracter(char *str)
{
	memmove(str, str + 1, strlen(str));	
}

char *ft_research_token(char *token, t_data *data)
{
	if (token[1] == '?')
		return (ft_itoa(data->exit_program));
	return (ft_env_tab_get_null(data->env->envp, token + 1));
}

void	join_add_node(t_list **begin, t_list *add)
{
	if (add)
	{
		if (*begin)
			ft_lstlast(*begin)->next = add;
		else
			*begin = add;
	}
}

int	join_create_set_node(t_list **begin, char *buffer, int type)
{
	t_list	*newnode;

	if (buffer == NULL)
		return (FAIL);
	newnode = ft_word_lst_make_join(buffer, type);
	if (newnode == NULL)
	{
		free(buffer);
		return (FAIL);
	}
	join_add_node(begin, newnode);
	return (SUCCESS);
}
