/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:05:05 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/09 16:50:21 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define SIGNAL_HANDLING 0
# define SIGNAL_CRASH 1

void	ft_check_args_main(int argc);

void	ft_use_line(void);

int		ft_signal(void);

void	ft_pwd_init(char **content);
char	*ft_pwd_get(void);

char	*ft_path_parser(const char *path, const char *change_path);
char	*ft_path_tab_to_str(char **pwd);

#endif