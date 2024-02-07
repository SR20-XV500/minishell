/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:48:43 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/07 21:21:23 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_pwd_is_arg(char **argv)
{
	int	ret;

	ret = IS_NOT_ARG;
	if (argv && *argv)
	{
		argv++;
		if (argv && (*argv)[0] == '-' && (*argv)[1] != '\0')
			ret = IS_ARG;
	}
	return (ret);
}

int	ft_pwd(char **argv, char **envp)
{
	int	ret;

	ret = 0;
	if (ft_pwd_is_arg(argv) == IS_ARG)
	{
		ft_fprintf(2, "minishell: pwd: not accept option");
		ret = 2;
	}
	else
		ft_printf("%s\n", ft_pwd_get());
	(void)envp;
	return (ret);
}
