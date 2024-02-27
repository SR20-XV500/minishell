/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:57:33 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/27 17:49:52 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_get_pos(t_env env, const char *name)
{
	return (ft_env_tab_get_pos(env.envp, name));
}

static char	*ft_env_ambiguous_variable(t_env env, const char *name)
{
	char	*content;

	content = NULL;
	if (name)
	{
		if (ft_strncmp("PATH", name, 5) == CMP_EGAL)
		{
			if (env.path)
				content = ft_strdup(env.path);
		}
		else if (ft_strncmp("?", name, 2) == CMP_EGAL)
			content = ft_itoa(env.exit_status);
		else
			content = ft_calloc(1, sizeof(char));
	}
	return (content);
}

char	*ft_env_get_content(t_env env, const char *name)
{
	char	*buffer;

	buffer = NULL;
	if (ft_env_get_pos(env, name) == ENV_NOT_SET)
		buffer = ft_env_ambiguous_variable(env, name);
	else
		buffer = ft_env_tab_get_content(env.envp, name);
	return (buffer);
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
