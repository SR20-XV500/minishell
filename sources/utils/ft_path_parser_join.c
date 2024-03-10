/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_parser_join.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:45:47 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/09 16:47:15 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_path_join(const char *s1, const char *s2)
{
	char	*buffer;
	char	*new_content;

	new_content = NULL;
	buffer = ft_strjoin(s2, "/");
	if (buffer)
	{
		if (s1)
		{
			new_content = ft_strjoin(s1, buffer);
			free(buffer);
		}
		else
			new_content = buffer;
	}
	return (new_content);
}

char	*ft_path_tab_to_str(char **pwd)
{
	char	*new_path;
	char	*buffer;
	int		status;

	buffer = NULL;
	new_path = NULL;
	status = SUCCESS;
	if (pwd && *pwd)
	{
		while (*pwd && status == SUCCESS)
		{
			buffer = ft_path_join(new_path, *pwd);
			if (new_path)
				free(new_path);
			new_path = buffer;
			if (buffer == NULL)
				status = MALLOC_FAIL;
			pwd++;
		}
	}
	else if (pwd)
		new_path = ft_strdup("/");
	return (new_path);
}
