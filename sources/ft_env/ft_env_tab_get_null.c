/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_tab_get_null.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:57:11 by tlassere          #+#    #+#             */
/*   Updated: 2025/05/11 14:06:09 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env_tab_get_null(char **envp, const char *name)
{
	char	*content;
	int		pos;

	content = NULL;
	pos = ft_env_tab_get_pos(envp, name);
	if (pos != ENV_NOT_SET)
		content = ft_substr(envp[pos], ft_strlen(name) + 1,
				ft_strlen(envp[pos]));
	return (content);
}
