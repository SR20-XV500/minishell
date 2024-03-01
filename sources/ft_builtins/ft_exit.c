/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:36:22 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/01 19:39:18 by tlassere         ###   ########.fr       */
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

static int	ft_exit_arg_is_valible(const char *str)
{
	int	status;
	long long nbr;

	status = SUCCESS;
	if (ft_exit_is_number(str) == FAIL)
		status = FAIL;
	nbr = ft_atoll(str);
	if (ft_check_overflow(str, nbr) == FAIL)
		status = FAIL;
	if (status)
		printf("fail\n");
	return (status);
}

int	ft_exit(t_data *data, const char **argv)
{
	int	status;

	status = BAD_PARAMETER;
	if (data && argv)
	{
		if (ft_tab_len((char **)argv) == 1)
		{
			if (ft_printf("exit\n") == -1)
				status = 2;
			else
				status = data->env->exit_status;
		}
		//else if (ft_tab_len(argv) == 2 || ft_exit_arg_is_valible(argv[1]) != SUCCESS)
		//	status = ft_exit_get_status_arg();
		else
		{
			ft_printf("exit\n");
			ft_fprintf(2, "minishell: exit: too many arguments\n");
			status = 2;
		}
		ft_exit_arg_is_valible(argv[1]);
		//(void)ft_exit_arg_is_valible;
		data->exit_program = SUCCESS;
	}
	return (status);
}
