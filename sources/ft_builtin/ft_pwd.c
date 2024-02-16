/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:48:43 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/16 22:27:57 by bcheronn         ###   ########.fr       */
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
		ft_fprintf(2, "minishell: pwd: does not accept options");
		ret = 2;
	}
	else
		ft_printf("%s\n", ft_pwd_get());
	(void)envp;
	return (ret);
}
