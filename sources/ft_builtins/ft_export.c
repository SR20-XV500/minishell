/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:27:00 by bcheronn          #+#    #+#             */
/*   Updated: 2024/02/19 21:01:35 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **argv, char **envp)
{
	int	exit_code;

	exit_code = FAIL;
	if (envp && *envp)
	{
		if (argv && *argv)
			ft_printf("args -> parse and add or update\n");
		else
			ft_printf("no args -> print the values\n");
		exit_code = SUCCESS;
	}
	return (exit_code);
}
