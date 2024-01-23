/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:07:01 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/18 19:45:39 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcat_char(char *dst, int c)
{
	size_t	dst_index;
	size_t	src_index;
	char	src[2];

	src[0] = (char)c;
	src[1] = '\0';
	dst_index = ft_strlen(dst);
	src_index = 0;
	while (src[src_index])
	{
		dst[dst_index + src_index] = src[src_index];
		src_index++;
	}
	dst[dst_index + src_index] = '\0';
}

static char	*ft_itoa_rec(char **str, long int n, int len, int negatif)
{
	if (n < 0)
		return (ft_itoa_rec(str, -n, len, 1));
	if (n < 10)
	{
		if (*str == NULL)
		{
			*str = (char *)ft_calloc(len + 1 + negatif, sizeof(char));
			if (*str == NULL)
				return (NULL);
			if (negatif)
				ft_strcat_char(*str, '-');
		}
		ft_strcat_char(*str, (int)(n + '0'));
		return (*str);
	}
	else
	{
		if (ft_itoa_rec(str, n / 10, len + 1, negatif) == NULL)
			return (NULL);
		return (ft_itoa_rec(str, n % 10, len + 1, negatif));
	}
}

char	*ft_itoa(int n)
{
	char	*str;

	str = NULL;
	return (ft_itoa_rec(&str, n, 1, 0));
}
