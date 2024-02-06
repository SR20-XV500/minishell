/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:09:37 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/06 18:36:55 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_display_prompt(int status)
{
	if (status == CD_TO_MANY_ARGS)
		ft_fprintf(2, "minishell: cd: HOME not set");
	if (status == CD_HOME_NOT_SET)
		ft_fprintf(2, "minishell: cd: too many arguments");
}

static int	ft_check_args(char **argv, char **envp, int *exit_code)
{
	int	ret;
	int	arg_len;

	ret = FAIL;
	if (argv)
	{
		ret = SUCCESS;
		arg_len = ft_tab_len(argv);
		if (arg_len > 2)
			ret = CD_TO_MANY_ARGS;
		if (arg_len == 1 && ft_env_tab_get_pos(envp, "HOME") == -1)
			ret = CD_HOME_NOT_SET;
	}
	if (ret != SUCCESS)
	{
		*exit_code = 1;
		ft_display_prompt(ret);
	}
	return (ret);
}

int	ft_cd(char **argv, char **envp)
{
	int	exit_code;

	exit_code = 0;
	if (ft_check_args(argv, envp, &exit_code) == SUCCESS)
	{
		
	}
	return (exit_code);
}
