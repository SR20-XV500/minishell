/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:07:21 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/03 01:32:13 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf_utils.h"

int	ft_null(int *size, int fd)
{
	ssize_t	val;

	val = ft_putstr_fd("(null)", fd);
	if (val == -1 || size == NULL)
		return (-1);
	*size += (int)val;
	return (0);
}

int	ft_nil(int *size, int fd)
{
	ssize_t	val;

	val = ft_putstr_fd("(nil)", fd);
	if (val == -1 || size == NULL)
		return (-1);
	*size += (int)val;
	return (0);
}

int	ft_print_str(char *str, int *size, int fd)
{
	ssize_t	val;

	if (str == NULL)
		return (ft_null(size, fd));
	val = ft_putstr_fd(str, fd);
	if (val == -1 || size == NULL)
		return (-1);
	*size += (int)val;
	return (1);
}

int	ft_print_tab(char **tab, int *size, int fd)
{
	int	i;

	if (tab == NULL)
		return (ft_null(size, fd));
	i = 0;
	while (tab[i])
	{
		if (ft_print_str(tab[i], size, fd) == -1
			|| ft_print_char('\n', size, fd) == -1)
			return (-1);
		i++;
	}
	return (0);
}
