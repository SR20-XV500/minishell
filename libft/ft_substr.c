/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:20:05 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/19 21:28:27 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	max_len;

	if (!s)
		return (NULL);
	max_len = ft_strlen(s);
	if (start > max_len)
	{
		max_len = 0;
		start = 0;
	}
	else
		max_len -= start;
	if (max_len > len)
		max_len = len;
	substring = (char *)ft_calloc(max_len + 1, sizeof(char));
	if (substring == NULL)
		return (NULL);
	ft_strlcpy(substring, s + start, max_len + 1);
	return (substring);
}
