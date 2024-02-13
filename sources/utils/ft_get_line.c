/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:37:52 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/13 14:55:27 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_word(t_list *lst)
{
	if (lst)
	{
		ft_printf("%s ---> %d\n", ((t_word *)lst->content)->word,
			((t_word *)lst->content)->type);
		ft_print_word(lst->next);
	}
}

static char	**ft_get_line(void)
{
	char	**lines;
	char	*curent_line;

	lines = NULL;
	curent_line = readline("sr2.0 xv500 > ");
	if (curent_line)
	{
		lines = ft_split(curent_line, '\n');
		free(curent_line);
	}
	return (lines);
}

static void	ft_use_current_line(char **lines, t_data *data)
{
	size_t	i;

	i = 0;
	while (lines[i])
	{
		add_history(lines[i]);
		if (ft_parser(data, lines[i]) == SUCCESS)
			ft_print_word(data->words);
		ft_word_lst_clear(data);
		i++;
	}
}

void	ft_use_line(t_data *data)
{
	char	**lines;

	lines = ft_get_line();
	while (lines)
	{
		ft_use_current_line(lines, data);
		ft_tab_free(lines);
		lines = ft_get_line();
	}
	rl_clear_history();
}
