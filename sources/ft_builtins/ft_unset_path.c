/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:44:47 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/04 17:46:21 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unsetting_path(const char *arg, t_env *env)
{
	if (arg && env->path && ft_strncmp("PATH", arg, 5) == CMP_EGAL)
	{
		free(env->path);
		env->path = NULL;
	}
}
