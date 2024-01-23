/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_convert_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:24:07 by tlassere          #+#    #+#             */
/*   Updated: 2023/11/04 12:48:28 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_valid_base(char *base)
{
	size_t	i;

	i = 0;
	while (base[i])
	{
		if (ft_strchr(base + i + 1, base[i]) != NULL
			|| base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	if (i < 2)
		return (0);
	return (1);
}

static size_t	ft_get_size(int dec, size_t len_base)
{
	size_t	count;
	int		res;

	count = 1;
	res = dec;
	if (dec < 0)
	{
		while (res <= -((int)len_base))
		{
			res /= (int)len_base;
			count++;
		}
		count++;
	}
	else
	{
		while (res >= (int)len_base)
		{
			res /= (int)len_base;
			count++;
		}
	}
	return (count);
}

static char	*ft_get_conv(int dec, char *base, size_t len_base)
{
	char	*convert;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_get_size(dec, len_base);
	convert = ft_calloc(len + 1, sizeof(char));
	if (convert == NULL)
		return (NULL);
	if (i == 0 && dec < 0)
		convert[len - 1] = '-';
	if (i == 0 && dec < 0)
		len -= 1;
	while (i < len)
	{
		convert[i] = base[ft_abs(dec % (int)len_base)];
		dec /= (int)len_base;
		i++;
	}
	return (ft_strrev(convert));
}

char	*ft_int_convert_base(int dec, char *base)
{
	if (base == NULL || ft_valid_base(base) != 1)
		return (NULL);
	return (ft_get_conv(dec, base, ft_strlen(base)));
}
