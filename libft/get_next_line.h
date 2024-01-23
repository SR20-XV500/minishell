/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:20:47 by tlassere          #+#    #+#             */
/*   Updated: 2023/11/14 20:53:29 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 42
# include <stdlib.h>
# include <unistd.h>

int		ft_check_buffer(char *buffer, int fd);
char	*get_next_line(int fd);
char	*ft_line(char *s1, char *s2, size_t cp_at);

#endif