/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:37:52 by tlassere          #+#    #+#             */
/*   Updated: 2024/01/30 14:51:39 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	ft_use_current_line(char **lines)
{
	size_t	i;

	i = 0;
	while (lines[i])
	{
		add_history(lines[i]);
		printf("%s\n", lines[i]);
		i++;
	}
}

void	ft_use_line(void)
{
	char	**lines;

	lines = ft_get_line();
	while (lines)
	{
		ft_use_current_line(lines);
		ft_tab_free(lines);
		lines = ft_get_line();
	}
}
