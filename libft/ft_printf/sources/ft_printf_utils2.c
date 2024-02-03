/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:11:26 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/03 01:42:13 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf_utils.h"

int	ft_print_nbr(int nbr, int *size, int fd)
{
	char	*str_nbr;
	int		tmp;

	str_nbr = ft_itoa(nbr);
	if (str_nbr == NULL)
		return (-1);
	tmp = ft_print_str(str_nbr, size, fd);
	free(str_nbr);
	return (tmp);
}

int	ft_print_char(char c, int *size, int fd)
{
	ssize_t	val;

	val = ft_putchar_fd(c, fd);
	if (val == -1)
		return (-1);
	*size += 1;
	return (1);
}

int	ft_print_ptr(void *ptr, int *size, int fd)
{
	char	*buffer;
	char	*val_ptr;
	int		tmp;

	if (ptr == NULL)
		return (ft_nil(size, fd));
	buffer = ft_bt8_convert_base((t_bt8)ptr, "0123456789abcdef");
	if (buffer == NULL)
		return (-1);
	val_ptr = ft_strjoin("0x", buffer);
	free(buffer);
	if (val_ptr == NULL)
		return (-1);
	tmp = ft_print_str(val_ptr, size, fd);
	free(val_ptr);
	return (tmp);
}

int	ft_print_hex(int dec, int *size, int upper, int fd)
{
	char			*str;
	int				tmp;

	if (upper)
		str = ft_uint_convert_base((unsigned int)dec, "0123456789ABCDEF");
	else
		str = ft_uint_convert_base((unsigned int)dec, "0123456789abcdef");
	if (str == NULL)
		return (-1);
	tmp = ft_print_str(str, size, fd);
	free(str);
	return (tmp);
}

int	ft_print_uint(unsigned int nbr, int *size, int fd)
{
	char	*str;
	int		tmp;

	str = ft_uint_convert_base(nbr, "0123456789");
	if (str == NULL)
		return (-1);
	tmp = ft_print_str(str, size, fd);
	free(str);
	return (tmp);
}
