/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:07:21 by tlassere          #+#    #+#             */
/*   Updated: 2023/11/17 23:45:52 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf_utils.h"

int	ft_null(int *size)
{
	ssize_t	val;

	val = ft_putstr_fd("(null)", 1);
	if (val == -1 || size == NULL)
		return (-1);
	*size += (int)val;
	return (0);
}

int	ft_nil(int *size)
{
	ssize_t	val;

	val = ft_putstr_fd("(nil)", 1);
	if (val == -1 || size == NULL)
		return (-1);
	*size += (int)val;
	return (0);
}

int	ft_print_str(char *str, int *size)
{
	ssize_t	val;

	if (str == NULL)
		return (ft_null(size));
	val = ft_putstr_fd(str, 1);
	if (val == -1 || size == NULL)
		return (-1);
	*size += (int)val;
	return (1);
}

int	ft_print_tab(char **tab, int *size)
{
	int	i;

	if (tab == NULL)
		return (ft_null(size));
	i = 0;
	while (tab[i])
	{
		if (ft_print_str(tab[i], size) == -1
			|| ft_print_char('\n', size) == -1)
			return (-1);
		i++;
	}
	return (0);
}
