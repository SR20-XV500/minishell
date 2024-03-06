/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 19:44:47 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/06 19:19:09 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_path(const char *arg, t_env *env)
{
	if (arg && env->path && ft_strncmp("PATH", arg, 5) == CMP_EGAL)
	{
		free(env->path);
		env->path = NULL;
	}
}
