/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:05:05 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/16 23:51:57 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "ft_parsing.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <unistd.h>

# define SIGNAL_HANDLING 0
# define SIGNAL_CRASH 1
# define NON_NULL_MEMORY (void *)-1

void	ft_check_args_main(int argc);

void	ft_use_line(t_data *data);

int		ft_signal(void);

void	ft_pwd_init(char **content);
char	*ft_pwd_get(void);
void	ft_pwd_change_content(char *str);

char	*ft_path_parser(const char *path, const char *change_path);
char	*ft_path_tab_to_str(char **pwd);
char	*ft_path_multiple_file(const char *multie_path, const char *dest);
char	*ft_path_multiple_directory(const char *multie_path, const char *dest);

int		ft_is_file(const char *path);
int		ft_is_directory(const char *path);

#endif
