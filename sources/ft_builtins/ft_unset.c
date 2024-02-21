/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:39:18 by bcheronn          #+#    #+#             */
/*   Updated: 2024/02/17 23:02:32 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_env *env, const char *name)
{
	int	ret;

	ret = ENV_BAD_PARAMETER;
	if (env && name && *name)
		ret = ft_env_del(env, name);
	return (ret);
}
