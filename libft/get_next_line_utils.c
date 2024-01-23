/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:05:14 by tlassere          #+#    #+#             */
/*   Updated: 2023/11/04 12:47:09 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_move_buffer(char *buffer, size_t moving)
{
	size_t	start;

	start = 0;
	while ((start < BUFFER_SIZE && buffer[start] != '\n') && buffer[start])
		start++;
	start++;
	while ((moving + start < BUFFER_SIZE) && buffer[moving + start])
	{
		buffer[moving] = buffer[start + moving];
		moving++;
	}
	while (moving < BUFFER_SIZE)
	{
		buffer[moving] = '\0';
		moving++;
	}
	return (start - 1);
}

static char	*ft_cat(char *s1, char *s2, size_t max_s2)
{
	size_t	max_s1;
	size_t	i;
	char	*new_string;

	max_s1 = 0;
	i = 0;
	while (s1[max_s1])
		max_s1++;
	new_string = malloc((max_s1 + max_s2 + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	while (i < max_s1)
	{
		new_string[i] = s1[i];
		i++;
	}
	while (i - max_s1 < max_s2)
	{
		new_string[i] = s2[i - max_s1];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

int	ft_check_buffer(char *buffer, int fd)
{
	size_t	i;
	ssize_t	res_read;

	i = ft_move_buffer(buffer, 0);
	if (i == BUFFER_SIZE || i == BUFFER_SIZE - 1 || !(buffer[0]))
	{
		res_read = read(fd, buffer, BUFFER_SIZE);
		if (res_read < 0)
			return (-1);
		if (res_read > 0)
			return (1);
		return (0);
	}
	return (1);
}

char	*ft_line(char *s1, char *s2, size_t cp_at)
{
	size_t	index;
	char	*line;

	index = 0;
	if (s1 != NULL)
		return (ft_cat(s1, s2, cp_at));
	line = malloc(sizeof(char) * (cp_at + 1));
	if (line == NULL)
		return (NULL);
	while (index < cp_at)
	{
		line[index] = s2[index];
		index++;
	}
	line[index] = '\0';
	return (line);
}
