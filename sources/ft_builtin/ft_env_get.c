/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:57:33 by tlassere          #+#    #+#             */
/*   Updated: 2024/01/30 21:46:39 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_get_pos(t_env env, char *str)
{
	int	pos;

	pos = -1;
	if (env.envp && str)
	{
		pos = 0;
		while (env.envp[pos] && (ft_strcmp_s2(env.envp[pos], str)
				|| env.envp[pos][ft_strlen(str)] != '='))
			pos++;
		if (env.envp[pos] == NULL)
			pos = -1;
	}
	return (pos);
}

char	*ft_env_get_content(t_env env, char *str)
{
	char	*content;
	int		pos;

	content = NULL;
	pos = ft_env_get_pos(env, str);
	if (pos != -1)
	{
		content = ft_substr(env.envp[pos], ft_strlen(str) + 1,
				ft_strlen(env.envp[pos]));
	}
	else
		content = ft_calloc(1, sizeof(char));
	return (content);
}
