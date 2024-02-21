/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:06:06 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/21 19:06:41 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cmd_free(t_cmd_content cmd_content)
{
	if (cmd_content.argv)
		ft_tab_free(cmd_content.argv);
	if (cmd_content.envp)
		ft_tab_free(cmd_content.envp);
	if (cmd_content.path)
		free(cmd_content.path);
}
