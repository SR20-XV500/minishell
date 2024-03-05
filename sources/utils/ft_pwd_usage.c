/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_usage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:58:59 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/06 00:17:52 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_pwd_usage(int flag, char **ptr_content, char *str)
{
	static char	**pwd = NULL;
	char		*pwd_content;

	pwd_content = NULL;
	if (flag == PWD_CHANGE_CONTENT && pwd)
	{
		if (*pwd)
			free(*pwd);
		*pwd = str;
	}
	if (flag == PWD_INIT && pwd == NULL)
		pwd = ptr_content;
	if (pwd && flag == PWD_GET)
		pwd_content = *pwd;
	return (pwd_content);
}

char	*ft_pwd_get(void)
{
	return (ft_pwd_usage(PWD_GET, NULL, NULL));
}

void	ft_pwd_init(char **content)
{
	if (content)
		ft_pwd_usage(PWD_INIT, content, NULL);
}
