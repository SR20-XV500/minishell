/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:48:43 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/06 00:10:30 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **argv, char **envp)
{
	int	ret;

	ret = SUCCESS;
	if (argv && argv[0])
		ret = ft_printf("%s\n", ft_pwd_get());
	if (ret == WRITE_FAIL)
		ret = FAIL;
	(void)envp;
	return (ret);
}
