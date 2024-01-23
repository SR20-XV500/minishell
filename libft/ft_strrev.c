/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:17:08 by tlassere          #+#    #+#             */
/*   Updated: 2023/11/01 12:35:32 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	size_t	len;
	size_t	i;
	char	temp;

	if (s == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	while (i < len / 2)
	{
		temp = s[len - 1 - i];
		s[len - 1 - i] = s[i];
		s[i] = temp;
		i++;
	}
	return (s);
}
