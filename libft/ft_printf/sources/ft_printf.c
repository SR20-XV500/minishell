/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:24:22 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/29 15:24:22 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"
#include "../headers/ft_printf_utils.h"

static int	ft_print_arg(const char *ptr, int *size, va_list arg, int fd)
{
	int	ret;

	ret = -12;
	if (ft_strcmp_s2(ptr, "%s") == 0)
		ret = ft_print_str(va_arg(arg, char *), size, fd);
	if (ft_strcmp_s2(ptr, "%w") == 0)
		ret = ft_print_tab(va_arg(arg, char **), size, fd);
	if (!(ft_strcmp_s2(ptr, "%d")) || !(ft_strcmp_s2(ptr, "%i")))
		ret = ft_print_nbr(va_arg(arg, int), size, fd);
	if (ft_strcmp_s2(ptr, "%u") == 0)
		ret = ft_print_uint(va_arg(arg, unsigned int), size, fd);
	if (ft_strcmp_s2(ptr, "%%") == 0)
		ret = ft_print_char('%', size, fd);
	if (ft_strcmp_s2(ptr, "%c") == 0)
		ret = ft_print_char((char)va_arg(arg, int), size, fd);
	if (ft_strcmp_s2(ptr, "%p") == 0)
		ret = ft_print_ptr(va_arg(arg, void *), size, fd);
	if (ft_strcmp_s2(ptr, "%x") == 0)
		ret = ft_print_hex(va_arg(arg, int), size, 0, fd);
	if (ft_strcmp_s2(ptr, "%X") == 0)
		ret = ft_print_hex(va_arg(arg, int), size, 1, fd);
	return (ret);
}

static int	ft_get_fd(const char *format, va_list arg, size_t *i, int old_fd)
{
	int	fd;

	fd = old_fd;
	if (ft_strcmp_s2(format, "%o") == 0)
	{
		fd = va_arg(arg, int);
		*i += 2;
	}
	return (fd);
}

int	ft_printf(const char *format, ...)
{
	int		size;
	int		tmp;
	int		fd;
	size_t	i;
	va_list	args;

	if (format == NULL)
		return (-1);
	i = 0;
	size = 0;
	fd = 1;
	va_start(args, format);
	while (format[i])
	{
		fd = ft_get_fd(format + i, args, &i, fd);
		if (format[i] == '\0')
			break ;
		tmp = ft_print_arg(format + i, &size, args, fd);
		if (tmp == -1
			|| (tmp == -12 && ft_print_char(format[i], &size, fd) == -1))
			return (-1);
		i += 1 + (tmp != -12);
	}
	va_end(args);
	return (size);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	int		size;
	int		tmp;
	size_t	i;
	va_list	args;

	if (format == NULL || fd <= -1)
		return (-1);
	i = 0;
	size = 0;
	va_start(args, format);
	while (format[i])
	{
		tmp = ft_print_arg(format + i, &size, args, fd);
		if (tmp == -1
			|| (tmp == -12 && ft_print_char(format[i], &size, fd) == -1))
			return (-1);
		i += 1 + (tmp != -12);
	}
	va_end(args);
	return (size);
}
