/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:36:22 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/06 19:29:48 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exit_is_number(const char *str)
{
	int		status;
	size_t	index;

	status = SUCCESS;
	index = 0;
	if ((str[index] == '+' || str[index] == '-') && str[index + 1])
		index++;
	while (str[index] && status == SUCCESS)
	{
		if (!(ft_isdigit(str[index])))
			status = FAIL;
		index++;
	}
	return (status);
}

static int	ft_exit_arg_is_valid(const char *str)
{
	int			status;
	long long	nbr;

	status = SUCCESS;
	if (ft_exit_is_number(str) == FAIL)
		status = FAIL;
	nbr = ft_atoll(str);
	if (ft_check_overflow(str, nbr) == OVERFLOW)
		status = FAIL;
	return (status);
}

static int	ft_exit_get_status_arg(const char *str)
{
	int	status;

	status = SUCCESS;
	if (ft_exit_arg_is_valid(str) == SUCCESS)
		status = (char)ft_atoll(str);
	else
	{
		status = EXIT_ERR;
		ft_fprintf(STDERR, "exit\n");
		ft_fprintf(STDERR, "minishell: exit: %s: numeric argument required\n",
			str);
	}
	return (status);
}

int	ft_exit(t_data *data, const char **argv)
{
	int	status;

	status = BAD_PARAMETER;
	if (data && argv)
	{
		data->exit_program = SUCCESS;
		if (ft_fprintf(STDERR, "exit\n") == -1)
			status = EXIT_ERR;
		if (ft_tab_len((char **)argv) == 1 && status != EXIT_ERR)
			status = data->env->exit_status;
		else if (ft_tab_len((char **)argv) == 2
			|| ft_exit_arg_is_valid(argv[1]) != SUCCESS)
			status = ft_exit_get_status_arg(argv[1]);
		else
		{
			ft_fprintf(STDERR, "minishell: exit: too many arguments\n");
			status = EXIT_ERR;
			data->exit_program = FAIL;
		}
	}
	return (status);
}
