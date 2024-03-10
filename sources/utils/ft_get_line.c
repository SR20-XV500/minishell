/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 01:37:52 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/10 15:09:09 by tlassere         ###   ########.fr       */
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

static int	ft_use_current_line(char **lines, t_data *data)
{
	int		exec_status;
	size_t	i;

	i = 0;
	exec_status = SUCCESS;
	while (lines[i] && data->exit_program && exec_status == SUCCESS)
	{
		if (g_signal_handle == SIGINT_SIGNAL)
			data->env->exit_status = g_signal_handle;
		g_signal_handle = 0;
		data->line_count += 1;
		add_history(lines[i]);
		if (ft_parser(data, lines[i]) == SUCCESS)
			exec_status = ft_exec(data);
		ft_word_lst_clear(data);
		ft_free_here_doc(&data->here_doc);
		ft_data_clear_fd(data);
		i++;
	}
	return (exec_status);
}

static int	ft_status_code(int status_code)
{
	int	status;

	status = SUCCESS;
	if (status_code == SIGNAL_CRASH
		|| status_code == DUP_FAIL_STATUS
		|| status_code == FD_FAIL_STATUS)
		status = FAIL;
	return (status);
}

void	ft_use_line(t_data *data)
{
	char	**lines;
	int		status;

	lines = ft_get_line();
	status = SUCCESS;
	while (lines && data->exit_program == FAIL && status == SUCCESS
		&& ft_signal_interactive() == SIGNAL_HANDLING)
	{
		data->tabs_lines = lines;
		status = ft_status_code(ft_use_current_line(lines, data));
		ft_tab_free(lines);
		data->tabs_lines = NULL;
		lines = NULL;
		if (ft_signal_interactive() == SIGNAL_HANDLING
			&& data->exit_program == FAIL)
			lines = ft_get_line();
	}
	if (lines)
		ft_tab_free(lines);
	if (data->exit_program == FAIL)
		ft_fprintf(STDERR, "exit\n");
	rl_clear_history();
}
