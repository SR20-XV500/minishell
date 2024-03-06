/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:22:40 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/06 23:59:27 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: with SIGINT return status code 130
// TODO: manage rl_clear_history on signal exit

int	g_signal_handle = 0;

static void	ft_interactive_sigint(int signal, siginfo_t *info, void *ucontext)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_signal_handle = SIGINT_SIGNAL;
	(void)ucontext;
	(void)info;
}

int	ft_signal_exec(void)
{
	int	status;

	status = SUCCESS;
	return (status);
}

int	ft_signal_interactive(void)
{
	int					ret;
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ret = SIGNAL_HANDLING;
	ft_memset(&sa_int, 0, sizeof(struct sigaction));
	sa_int.sa_flags = SA_SIGINFO;
	sa_int.sa_sigaction = &ft_interactive_sigint;
	ft_memset(&sa_quit, 0, sizeof(struct sigaction));
	sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		ret = SIGNAL_CRASH;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		ret = SIGNAL_CRASH;
	return (ret);
}
