/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:04:01 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/23 12:17:43 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buff;
	size_t	res;

	res = nmemb * size;
	if (size && nmemb && (res / nmemb != size))
		return (NULL);
	buff = malloc(nmemb * size);
	if (buff == NULL)
		return (NULL);
	ft_bzero(buff, nmemb * size);
	return (buff);
}
