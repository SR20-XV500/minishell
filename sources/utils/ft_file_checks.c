/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:29 by bcheronn          #+#    #+#             */
/*   Updated: 2024/02/14 15:44:02 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/stat.h>

int	ft_file_is_executable(const char *path)
{
	int			ret;
	struct stat	file_info;

	ret = stat(path, &file_info);
	if (ret == SUCCESS && file_info.st_mode & S_IXUSR)
		ret = SUCCESS;
	else
		ret = FAIL;
	return (ret);
}

int	ft_file_is_directory(const char *path)
{
	(void)path;
	return (SUCCESS);
}
