/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:07:41 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/19 13:40:06 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_revmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*buff_src;
	unsigned char	*buff_dest;

	i = 0;
	buff_src = (void *)src;
	buff_dest = dest;
	while (i < n)
	{
		buff_dest[n - i - 1] = buff_src[n - i - 1];
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == NULL || src == NULL)
		return (NULL);
	if (dest > src && dest < src + n)
		return (ft_revmove(dest, src, n));
	return (ft_memcpy(dest, src, n));
}
