/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_initial.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:28:56 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/02 19:28:58 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_init_value(t_env *env)
{
	int	ret;

	ret = MALLOC_FAIL;
	if (env)
	{
		if (ft_env_init_shlvl(env) == ENV_SUCCESS)
			ret = ENV_SUCCESS;
	}
	return (ret);
}
