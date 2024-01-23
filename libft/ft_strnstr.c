/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:16:17 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/18 13:06:54 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	len_hay;
	size_t	len_nee;

	if (big == NULL || little == NULL)
		return (NULL);
	i = 0;
	len_hay = ft_strlen(big);
	len_nee = ft_strlen(little);
	if (len_nee == 0)
		return ((char *)big);
	while ((i < len_hay) && (i + len_nee <= len))
	{
		if (!ft_strncmp((big + i), little, len_nee))
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
