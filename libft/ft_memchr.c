/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:07:16 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/18 11:39:02 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*buff;

	if (s == NULL)
		return (NULL);
	i = 0;
	buff = (void *)s;
	while (i < n)
	{
		if (buff[i] == (unsigned char)c)
			return ((void *)(buff + i));
		i++;
	}
	return (NULL);
}
