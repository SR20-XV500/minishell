/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:39:18 by bcheronn          #+#    #+#             */
/*   Updated: 2024/02/21 23:05:59 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **argv, t_env *env)
{
	int	ret;

	ret = ENV_BAD_PARAMETER;
	if (env && argv && argv[0] && argv[1])
	{
		while (*(++argv) && ret != MALLOC_FAIL)
			ret = ft_env_del(env, *argv);
	}
	if (ret != MALLOC_FAIL)
		ret = SUCCESS;
	return (ret);
}
