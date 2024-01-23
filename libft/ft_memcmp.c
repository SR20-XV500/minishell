/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:07:22 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/18 11:39:46 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_buff;
	unsigned char	*s2_buff;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	s1_buff = (void *)s1;
	s2_buff = (void *)s2;
	while (i < n)
	{
		if (s1_buff[i] != s2_buff[i])
			return (s1_buff[i] - s2_buff[i]);
		i++;
	}
	return (0);
}
