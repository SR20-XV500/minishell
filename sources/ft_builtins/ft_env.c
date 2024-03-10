/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:02:25 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/02 18:03:58 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(const char **envp)
{
	int	ret;

	ret = FAIL;
	if (envp && ft_printf("%w", envp) > 0)
		ret = SUCCESS;
	return (ret);
}
