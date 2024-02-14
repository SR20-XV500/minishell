/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:29 by bcheronn          #+#    #+#             */
/*   Updated: 2024/02/14 23:04:02 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_file(const char *path)
{
	int	ret;

	ret = BAD_PARAMETER;
	if (path && *path)
		;
	return (ret);
}

int	ft_file_is_directory(const char *path)
{
	(void)path;
	return (SUCCESS);
}
