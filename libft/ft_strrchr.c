/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:17:26 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/20 13:47:04 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*buffer;

	if (s == NULL)
		return (NULL);
	i = 0;
	buffer = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			buffer = (char *)(s + i);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(s + i));
	return (buffer);
}
