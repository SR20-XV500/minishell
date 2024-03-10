/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_overflow.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:13:37 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/02 01:03:39 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_overflow(const char *str, long long nbr)
{
	size_t		i;
	int			ret;
	long long	nbr_cpy;

	ret = BAD_PARAMETER;
	if (str && *str)
	{
		nbr_cpy = nbr;
		ret = OVERFLOW;
		i = ft_strlen(str) - 1;
		while (ft_abs((int)(nbr % 10)) + '0' == str[i] && i)
		{
			nbr /= 10;
			i--;
		}
		if ((ft_strchr("+-", str[i]) || ft_abs((int)(nbr % 10)) + '0' == str[i])
			&& nbr < 10 && nbr > -10 && i == 0)
			ret = SUCCESS;
		if ((str[0] == '-' && nbr_cpy > 0) || (str[0] != '-' && nbr_cpy < 0))
			ret = OVERFLOW;
	}
	return (ret);
}
