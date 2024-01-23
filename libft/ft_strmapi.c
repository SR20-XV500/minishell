/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:13:22 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/17 14:13:23 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*buffer;
	size_t	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	buffer = ft_strdup(s);
	if (buffer == NULL)
		return (NULL);
	while (buffer[i])
	{
		buffer[i] = (*f)(i, buffer[i]);
		i++;
	}
	return (buffer);
}
