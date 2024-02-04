/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:22:40 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/04 20:48:03 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_get_signal(int signal, siginfo_t *info, void *ucontext)
{
	if (signal == SIGINT)
		rl_on_new_line();
	(void)ucontext;
	(void)info;
}

int	ft_signal(void)
{
	int					ret;
	struct sigaction	sa;

	ret = SIGNAL_HANDLING;
	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &ft_get_signal;
	if (sigaction(SIGINT, &sa, NULL) == -1
		|| sigaction(SIGQUIT, &sa, NULL) == -1)
		ret = SIGNAL_CRASH;
	return (ret);
}
