/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:31:36 by tlassere          #+#    #+#             */
/*   Updated: 2023/11/03 17:37:55 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	free_buffer(char *line, char *b_line, char *buffer, size_t i)
{
	if (b_line != NULL)
		free(b_line);
	else if (line == NULL)
		return (-1);
	if (i != BUFFER_SIZE && buffer[i] == '\n')
		return (1);
	return (0);
}

static char	*ft_get_cur_line(char *buffer, int fd)
{
	char	*line;
	char	*buffer_line;
	int		res;
	size_t	i;

	line = NULL;
	res = ft_check_buffer(buffer, fd);
	while (res > 0)
	{
		i = 0;
		buffer_line = line;
		while (i < BUFFER_SIZE && buffer[i] != '\n' && buffer[i])
			i++;
		if (i != BUFFER_SIZE && buffer[i] != '\0')
			line = ft_line(buffer_line, buffer, i + 1);
		else
			line = ft_line(buffer_line, buffer, i);
		res = free_buffer(line, buffer_line, buffer, i);
		if (res != 0)
			return (line);
		res = ft_check_buffer(buffer, fd);
	}
	if (res == -1 && line)
		return (free(line), NULL);
	return (line);
}

static char	*ft_get_next_line_reader(int fd)
{
	static char	buff[BUFFER_SIZE] = {0};
	char		*line;

	line = ft_get_cur_line(buff, fd);
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (BUFFER_SIZE > 100000000)
		return (NULL);
	return (ft_get_next_line_reader(fd));
}
