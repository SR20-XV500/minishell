/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:48:43 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/06 00:20:00 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **argv, t_env *env)
{
	int	ret;

	ret = SUCCESS;
	if (argv && argv[0])
		ret = ft_printf("%s\n", env->pwd);
	if (ret == WRITE_FAIL)
		ret = FAIL;
	return (ret);
}
