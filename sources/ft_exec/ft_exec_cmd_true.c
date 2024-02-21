/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_true.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:38:33 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/21 20:03:32 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_cmd_true(t_data *data, const t_cmd_content cmd)
{
	int	status;

	status = BAD_PARAMETER;
	if (cmd.argv && *(cmd.argv) && cmd.envp && cmd.path)
	{
		status = SUCCESS;
	}
	return (status);
}
