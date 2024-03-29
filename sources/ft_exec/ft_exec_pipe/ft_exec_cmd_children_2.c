/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_children_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 22:38:12 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/08 22:32:04 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_children(t_data *data, pid_t *children, int len)
{
	int	index;
	int	tmp;

	index = 0;
	tmp = 0;
	if (data && children && len > 0)
	{
		while (index < len)
		{
			waitpid(children[index], &tmp, 0);
			data->env->exit_status = WEXITSTATUS(tmp);
			index++;
		}
	}
}

void	ft_kill_children(pid_t *children, int len)
{
	if (children && len > 0)
	{
		while (len)
		{
			len--;
			kill(children[len], SIGKILL);
		}
	}
}
