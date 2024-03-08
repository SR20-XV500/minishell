/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:43:24 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/08 16:48:10 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_sigint(int signals, siginfo_t *info, void *ucontext)
{
	if (signals == SIGINT)
	{
		close(STDIN);
		signal(SIGINT, SIG_IGN);
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_handle = SIGINT_SIGNAL;
	}
	(void)ucontext;
	(void)info;
}

int	ft_signal_heredoc(void)
{
	int					status;
	struct sigaction	sa_int;

	status = SIGNAL_HANDLING;
	ft_memset(&sa_int, 0, sizeof(struct sigaction));
	sa_int.sa_flags = SA_SIGINFO;
	sa_int.sa_sigaction = &ft_heredoc_sigint;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		status = SIGNAL_CRASH;
	return (status);
}
