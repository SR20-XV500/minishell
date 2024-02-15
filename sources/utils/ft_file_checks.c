/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:29 by bcheronn          #+#    #+#             */
/*   Updated: 2024/02/15 00:32:43 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_file(const char *path)
{
	int	ret;

	ret = BAD_PARAMETER;
	if (path != NULL && *path != '\0')
	{
		if (access(path, F_OK) == SUCCESS)
			ret = SUCCESS;
		else
			ret = FAIL;
	}
	return (ret);
}

int	ft_is_directory(const char *path)
{
	int			ret;
	struct stat	file_info;

	ret = BAD_PARAMETER;
	if (path != NULL && *path != '\0')
	{
		if (stat(path, &file_info) == SUCCESS && S_ISDIR(file_info.st_mode))
			ret = SUCCESS;
		else
			ret = FAIL;
	}
	return (ret);
}
