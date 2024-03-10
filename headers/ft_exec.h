/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:13:28 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/10 23:01:56 by tlassere         ###   ########.fr       */
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
# define EXEC_CMD_NOT_FOUND_DIR 126
# define EXEC_CMD_PERMISSION_DENIED 126
# define REDIRECT_FAIL 1
# define OPEN_WR_R_R 0644
# define FD_FAIL_OPEN -1
# define MAX_OPEN_PRE_OPEN 2
# define EXEC_DUP_FAIL -1
# define NO_PRIORITY 1
# define PRIORITY_HERE_DOC 2
# define PRIORITY_INPUT 3
# define ERR_HERE_DOC "minishell: warning: here-document at line %d "
# define ERR_HERE_DOC_2 "delimited by end-of-file (wanted `%s')\n"
# define ERR_PIPE_FAIL -16

typedef struct s_cmd_content
{
	char	**argv;
	char	**envp;
	char	*path;
}			t_cmd_content;

typedef struct s_redirect
{
	int	fd;
	int	type;
}			t_redirect;

char		*ft_redirect_get_path(t_data *data, const char *str);
char		*ft_trim_ambiguous(char *str);
int			ft_exec_redirect_fd(t_data *data, int type, const char *path,
				const char *err_str);

int			ft_exec_here_doc(t_data *data);
int			ft_exec_here_doc_redirect(t_data *data, t_list *lst_start);
t_list		*ft_here_doc_delimiter(t_data *data, char *str);
int			ft_exec_here_doc_func(t_data *data);
int			ft_open_new(void);

int			ft_exec_dupbass(t_data *data);
int			ft_exec_dup_close(t_data *data);

int			ft_redirect_priority(t_list *lst);

int			ft_word_count(t_list *lst, int type);
void		ft_wait_children(t_data *data, pid_t *children, int len);
void		ft_kill_children(pid_t *children, int len);
int			ft_crazy_children(t_data *data, int *fds, int len, pid_t *children);
int			ft_exec_pipe(t_data *data);
void		ft_close_pipe(int *fds, int len);

int			ft_exec(t_data *data);
int			ft_exec_basic(t_data *data, t_list *lst_start);
int			ft_exec_cmd(t_data *data, t_list *lst);
void		ft_exec_cmd_free(const t_cmd_content cmd_content);
char		*ft_exec_cmd_get_path(t_data *data, const char *cmd_name);
int			ft_exec_cmd_true(t_data *data, const t_cmd_content cmd,
				const char *name);
int			ft_exec_display_error_execve(const t_cmd_content cmd,
				const char *buff);
int			ft_exec_redirect(t_data *data, t_list *lst);
int			ft_is_builtin(const char *cmd);

#endif
