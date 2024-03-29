/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:22:40 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/09 00:50:34 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_handle = 0;

static void	ft_interactive_sigint(int signal, siginfo_t *info, void *ucontext)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_handle = SIGINT_SIGNAL;
	}
	(void)ucontext;
	(void)info;
}

static void	ft_exec_handle(int signals, siginfo_t *info, void *ucontext)
{
	if (signals == SIGINT)
		g_signal_handle = SIGINT_SIGNAL;
	if (signals == SIGQUIT)
		g_signal_handle = SIGQUIT_SIGNAL;
	(void)ucontext;
	(void)info;
}

int	ft_signal_ing(void)
{
	int	status;

	status = SIGNAL_HANDLING;
	if (signal(SIGINT, SIG_IGN) == SIG_ERR
		|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		status = SIGNAL_CRASH;
	return (status);
}

int	ft_signal_exec(void)
{
	int					status;
	struct sigaction	sa_exec;

	status = SIGNAL_HANDLING;
	ft_memset(&sa_exec, 0, sizeof(struct sigaction));
	sa_exec.sa_flags = SA_SIGINFO;
	sa_exec.sa_sigaction = &ft_exec_handle;
	if (sigaction(SIGINT, &sa_exec, NULL) == SIGACTION_FAIL)
		status = SIGNAL_CRASH;
	if (sigaction(SIGQUIT, &sa_exec, NULL) == SIGACTION_FAIL)
		status = SIGNAL_CRASH;
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
	if (sigaction(SIGQUIT, &sa_quit, NULL) == SIGACTION_FAIL)
		ret = SIGNAL_CRASH;
	if (sigaction(SIGINT, &sa_int, NULL) == SIGACTION_FAIL)
		ret = SIGNAL_CRASH;
	return (ret);
}
