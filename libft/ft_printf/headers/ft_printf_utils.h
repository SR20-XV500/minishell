/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:05:08 by tlassere          #+#    #+#             */
/*   Updated: 2023/11/17 22:59:58 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H
# include "../../libft.h"
# include <stdarg.h>

int	ft_null(int *size);
int	ft_nil(int *size);
int	ft_print_str(char *str, int *size);
int	ft_print_char(char c, int *size);
int	ft_print_nbr(int nbr, int *size);
int	ft_print_ptr(void *ptr, int *size);
int	ft_print_hex(int dec, int *size, int upper);
int	ft_print_uint(unsigned int nbr, int *size);
int	ft_print_tab(char **tab, int *size);

#endif