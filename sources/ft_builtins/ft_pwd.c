/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:48:43 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/21 20:50:36 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **argv, char **envp)
{
	int	ret;

	ret = 0;
	if (argv && argv[0] && argv[1])
	{
		ft_fprintf(2, "minishell: pwd: does not accept options");
		ret = 2;
	}
	else
		ft_printf("%s\n", ft_pwd_get());
	(void)envp;
	return (ret);
}
