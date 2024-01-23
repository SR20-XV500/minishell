/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:09:28 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/17 20:12:30 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len_src;

	if (dst == NULL || src == NULL)
		return (0);
	len_src = ft_strlen(src);
	if (len_src + 1 < size)
		ft_memcpy(dst, src, len_src + 1);
	else if (size != 0)
	{
		ft_memcpy(dst, src, size -1);
		dst[size - 1] = '\0';
	}
	return (len_src);
}
