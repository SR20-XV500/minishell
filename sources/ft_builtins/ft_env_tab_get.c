/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_tab_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 22:18:17 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/19 22:36:08 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_tab_get_pos(char **envp, const char *name)
{
	int				pos;
	unsigned int	len;

	pos = -1;
	if (envp && name)
	{
		pos = 0;
		len = ft_strlen(name);
		while (envp[pos] && (ft_strcmp_s2(envp[pos], name)
				|| envp[pos][len] != '='))
			pos++;
		if (envp[pos] == NULL)
			pos = -1;
	}
	return (pos);
}

char	*ft_env_tab_get_content(char **envp, const char *name)
{
	char	*content;
	int		pos;

	content = NULL;
	pos = ft_env_tab_get_pos(envp, name);
	if (pos != -1)
	{
		content = ft_substr(envp[pos], ft_strlen(name) + 1,
				ft_strlen(envp[pos]));
	}
	else
		content = ft_calloc(1, sizeof(char));
	return (content);
}

int	ft_env_tab_del(char ***envp, const char *name)
{
	char	**buffer;
	int		ret;
	int		pos;

	ret = ENV_BAD_PARAMETER;
	if (envp && name)
	{
		ret = ENV_NOT_EXISTING_VARIABLE;
		pos = ft_env_tab_get_pos(*envp, name);
		if (pos != -1)
		{
			ret = MALLOC_FAIL;
			buffer = ft_tab_del(*envp, pos);
			if (buffer)
			{
				ret = ENV_SUCCESS;
				*envp = buffer;
			}
		}
	}
	return (ret);
}

static int	ft_env_tab_add_content(char ***envp, const char *all_str)
{
	int		ret;
	char	**table;

	ret = MALLOC_FAIL;
	table = ft_tab_join(*envp, all_str);
	if (table)
	{
		ret = ENV_SUCCESS;
		*envp = table;
	}
	return (ret);
}

int	ft_env_tab_add(char ***envp, const char *all_str)
{
	int		ret;
	char	*name;

	ret = ENV_BAD_PARAMETER;
	if (envp && *envp && all_str)
	{
		name = ft_env_get_name(all_str);
		if (name && ft_env_tab_get_pos(*envp, name) == -1)
			ret = ft_env_tab_add_content(envp, all_str);
		else if (name == NULL)
			ret = MALLOC_FAIL;
		else
			ret = ENV_EXISTING_VARIABLE;
		free(name);
	}
	return (ret);
}
