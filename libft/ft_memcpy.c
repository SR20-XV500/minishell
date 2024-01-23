/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:07:31 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/19 14:15:55 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_buff;
	unsigned char	*src_buff;

	if (dest == NULL || src == NULL)
		return (NULL);
	dest_buff = dest;
	src_buff = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dest_buff[i] = src_buff[i];
		i++;
	}
	return (dest);
}
