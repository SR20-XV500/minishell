/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:14:43 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/10 20:43:55 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_arg(char *str)
{
	int	ret;
	int	buffer;

	ret = IS_NOT_ARG;
	buffer = FAIL;
	if (str && *str == '-')
	{
		str++;
		while (*str == 'n')
		{
			str++;
			buffer = SUCCESS;
		}
		if (*str == '\0' && buffer == SUCCESS)
			ret = IS_ARG;
	}
	return (ret);
}

static int	ft_print_arg(char **argv)
{
	int	triger;
	int	error;
	int	first;

	triger = 0;
	error = 0;
	first = 0;
	while (*argv && error != -1)
	{
		if (ft_is_arg(*argv) == IS_NOT_ARG)
			triger = 1;
		if (triger)
		{
			if (first)
				ft_printf(" ");
			error = ft_printf("%s", *argv);
			first = 1;
		}
		argv++;
	}
	return ((error == -1));
}

int	ft_echo(char **argv)
{
	int	flag;
	int	ret;

	ret = FAIL;
	flag = IS_NOT_ARG;
	if (argv)
	{
		argv++;
		flag = ft_is_arg(argv[0]);
		ft_print_arg(argv);
		ret = SUCCESS;
	}
	if (flag == IS_NOT_ARG)
		ft_printf("\n");
	return (ret);
}
