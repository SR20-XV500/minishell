/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:13:28 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/22 21:06:09 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXEC_H
# define FT_EXEC_H

# include "ft_parsing.h"
# include <sys/wait.h>

# define REDIRECT_AMBIGUOUS_REDIRECT 26
# define ERR_SUCH_FILE "minishell: %s: No such file or directory\n"
# define ERR_AMBIGUOUS_REDIRECT "minishell: %s: ambiguous redirect\n"
# define CHILDREN 0
# define EXIT_MODE 255
# define NO_OPTION 0
# define CHILDREN_FAIL -1
# define EXEC_CMD_NOT_FOUND 127
# define REDIRECT_FAIL 1
# define OPEN_WR_R_R 0644
# define FD_FAIL_OPEN -1
# define MAX_OPEN_PRE_OPEN 2
# define EXEC_DUP_FAIL -1

typedef struct s_cmd_content
{
	char	**argv;
	char	**envp;
	char	*path;
}	t_cmd_content;

char	*ft_redirect_get_path(t_data *data, const char *str);
int		ft_exec(t_data *data);
int		ft_exec_redirect_fd(t_data *data, int type,
			const char *path, const char *err_str);
int		ft_exec_redirect(t_data *data, t_list *lst);
char	*ft_exec_cmd_get_path(t_data *data, const char *cmd_name);
int		ft_exec_cmd(t_data *data, t_list *lst);
int		ft_is_builtin(const char *cmd);
void	ft_exec_cmd_free(const t_cmd_content cmd_content);
int		ft_exec_cmd_true(t_data *data, const t_cmd_content cmd,
			const char *name);
int		ft_exec_dupbass(t_data *data);
int		ft_exec_dup_close(t_data *data);

#endif
