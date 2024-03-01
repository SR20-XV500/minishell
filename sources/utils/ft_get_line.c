/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:37:52 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/29 23:37:58 by tlassere         ###   ########.fr       */
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
	(void)ft_print_word;
	while (lines[i])
	{
		data->line_count += 1;
		add_history(lines[i]);
		if (ft_parser(data, lines[i]) == SUCCESS)
		{
			if (ft_exec(data) == SUCCESS)
			{
			}
		}
		ft_word_lst_clear(data);
		ft_free_here_doc(&data->here_doc);
		i++;
	}
}

void	ft_use_line(t_data *data)
{
	char	**lines;

	lines = ft_get_line();
	while (lines)
	{
		data->tabs_lines = lines;
		ft_use_current_line(lines, data);
		ft_tab_free(lines);
		data->tabs_lines = NULL;
		lines = ft_get_line();
	}
	ft_printf("\n");
	rl_clear_history();
}
