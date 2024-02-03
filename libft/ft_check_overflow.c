/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_overflow.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:13:37 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/02 23:03:04 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_overflow(const char *str, long long nbr)
{
	size_t	i;
	int		ret;

	ret = BAD_PARAMETER;
	if (str && *str)
	{
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
	}
	return (ret);
}
