/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:57:33 by tlassere          #+#    #+#             */
/*   Updated: 2024/01/31 19:41:35 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_get_pos(t_env env, const char *name)
{
	int				pos;
	unsigned int	len;

	pos = -1;
	if (env.envp && name)
	{
		pos = 0;
		len = ft_strlen(name);
		while (env.envp[pos] && (ft_strcmp_s2(env.envp[pos], name)
				|| env.envp[pos][len] != '='))
			pos++;
		if (env.envp[pos] == NULL)
			pos = -1;
	}
	return (pos);
}

char	*ft_env_get_content(t_env env, const char *name)
{
	char	*content;
	int		pos;

	content = NULL;
	pos = ft_env_get_pos(env, name);
	if (pos != -1)
	{
		content = ft_substr(env.envp[pos], ft_strlen(name) + 1,
				ft_strlen(env.envp[pos]));
	}
	else
		content = ft_calloc(1, sizeof(char));
	return (content);
}

char	*ft_env_get_name(const char *all_str)
{
	char	*name;

	name = NULL;
	if (all_str)
	{
		if (ft_strchr(all_str, '='))
			name = ft_substr(all_str, 0, ft_strchr(all_str, '=') - all_str);
		else
			name = ft_strdup(all_str);
	}
	return (name);
}
