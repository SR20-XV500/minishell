/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:22:40 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/05 16:22:40 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: with SIGINT return status code 130

static void	ft_get_signal(int signal, siginfo_t *info, void *ucontext)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	//if (signal == SIGQUIT)
	//{
		
	//	rl_on_new_line();
	//	rl_redisplay();
	//}
	(void)ucontext;
	(void)info;
}


void	ft_saquit(int signal, siginfo_t *info, void *ucontext)
{
	struct sigaction	sa_quit;

	ft_memset(&sa_quit, 0, sizeof(struct sigaction));
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
	(void)ucontext;
	(void)info;
	(void)signal;
}

int	ft_signal(void)
{
	int					ret;
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ret = SIGNAL_HANDLING;
	ft_memset(&sa_int, 0, sizeof(struct sigaction));
	ft_memset(&sa_quit, 0, sizeof(struct sigaction));
	sa_int.sa_flags = SA_SIGINFO;
	sa_int.sa_sigaction = &ft_get_signal;
	sa_quit.sa_flags = SA_SIGINFO;
	sa_quit.sa_sigaction = &ft_saquit;
	
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		ret = SIGNAL_CRASH;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		ret = SIGNAL_CRASH;
	return (ret);
}
