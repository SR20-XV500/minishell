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

static int	ft_print_arg(const char *ptr, size_t *i, int *size, va_list arg)
{
	int	ret;

	ret = -12;
	if (ft_strcmp_s2(ptr + *i, "%s") == 0)
		ret = ft_print_str(va_arg(arg, char *), size);
	if (ft_strcmp_s2(ptr + *i, "%w") == 0)
		ret = ft_print_tab(va_arg(arg, char **), size);
	if (!(ft_strcmp_s2(ptr + *i, "%d")) || !(ft_strcmp_s2(ptr + *i, "%i")))
		ret = ft_print_nbr(va_arg(arg, int), size);
	if (ft_strcmp_s2(ptr + *i, "%u") == 0)
		ret = ft_print_uint(va_arg(arg, unsigned int), size);
	if (ft_strcmp_s2(ptr + *i, "%%") == 0)
		ret = ft_print_char('%', size);
	if (ft_strcmp_s2(ptr + *i, "%c") == 0)
		ret = ft_print_char((char)va_arg(arg, int), size);
	if (ft_strcmp_s2(ptr + *i, "%p") == 0)
		ret = ft_print_ptr(va_arg(arg, void *), size);
	if (ft_strcmp_s2(ptr + *i, "%x") == 0)
		ret = ft_print_hex(va_arg(arg, int), size, 0);
	if (ft_strcmp_s2(ptr + *i, "%X") == 0)
		ret = ft_print_hex(va_arg(arg, int), size, 1);
	if (ret != -12)
		return ((*i += 1), ret);
	return (ft_print_char(ptr[*i], size));
}

int	ft_printf(const char *format, ...)
{
	int		size;
	size_t	i;
	va_list	args;

	if (format == NULL)
		return (-1);
	i = 0;
	size = 0;
	va_start(args, format);
	while (format[i])
	{
		if (ft_print_arg(format, &i, &size, args) == -1)
			return (-1);
		i++;
	}
	va_end(args);
	return (size);
}
