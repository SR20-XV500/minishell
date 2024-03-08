/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:05:05 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/08 16:10:21 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <unistd.h>

# define SIGNAL_HANDLING 0
# define SIGNAL_CRASH 1
# define FD_FAIL_STATUS 56
# define DUP_FAIL_STATUS 57

# define SIGINT_SIGNAL 130
# define SIGQUIT_SIGNAL 131

extern int	g_signal_handle;

void	ft_check_args_main(int argc);

void	ft_use_line(t_data *data);

int		ft_signal_interactive(void);
int		ft_signal_exec(void);
int		ft_signal_heredoc(void);

void	ft_pwd_init(char **content);

char	*ft_path_parser(const char *path, const char *change_path);
char	*ft_path_tab_to_str(char **pwd);
char	*ft_path_multiple_file(const char *multie_path, const char *dest,
			t_env *env);

int		ft_is_file(const char *path);
int		ft_is_directory(const char *path);

void	ft_strings_quicksort(char **array, int lower_index, int higher_index);

#endif
