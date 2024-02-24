/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:27:00 by bcheronn          #+#    #+#             */
/*   Updated: 2024/02/25 00:31:09 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **argv, t_env *env)
{
	int	exit_code;

	exit_code = FAIL;
	if (env)
	{
		if (argv && argv[0] && argv[1])
		{
			ft_printf("args -> parse and add or update\n");
			exit_code = SUCCESS;
		}
		else
			exit_code = ft_export_print(env);
	}
	return (exit_code);
}
