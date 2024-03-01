/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:21:58 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/01 17:27:36 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSING_H
# define FT_PARSING_H

# include "ft_env.h"

# define PARSER_WORD 12
# define PARSER_NO_WORD 13
# define PARSER_ERR_OP_NEWLINE 1
# define PARSER_NEAR_PIPE 2
# define PARSER_EXPANSION_VAR_CHANGE 14
# define PARSER_EXPANSION_VAR_NO_CHANGE 15
# define PARSER_GOOD_QUOTE 0
# define PARSER_BAD_QUOTE 1
# define NO_CHANGE_LST 26

enum e_delimiter
{
	D_NOT_SET = 50,
	D_PIPE,
	D_HEREDOC,
	D_INPUT,
	D_OUTPUT_APPEND,
	D_OUTPUT_NEW,
	D_QUOTE_ONE,
	D_QUOTE_TWO,
	D_NEW_LINE,
};

enum e_type
{
	TY_NOT_SET = 70,
	TY_ARG,
	TY_CMD,
	TY_PATH,
	TY_DELIM_HEREDOC
};

enum e_heredoc
{
	HER_STR = 90,
	HER_EOF
};

typedef struct s_word
{
	char	*word;
	int		type;
}	t_word;

typedef struct s_data
{
	t_env	*env;
	t_list	*words;
	int		dup_std[2];
	int		output_fd;
	int		input_fd;
	pid_t	*children;
	size_t	line_count;
	t_list	**here_doc;
	char	**tabs_lines;
	int		exit_program;
}	t_data;

t_data	*ft_data_get(const char **envp);
void	ft_data_free(t_data **data);
void	ft_free_here_doc(t_list ***here_doc);

void	ft_word_lst_clear(t_data *data);
void	ft_word_free(void *data);
int		ft_word_add(t_data *data, const char *str, int type);
t_list	*ft_word_lst_make(const char *str, int type);
int		ft_word_add_lst(t_list **lst_el, const char *str, int type);

int		ft_parser(t_data *data, const char *str);
int		ft_parser_use_line(t_data *data, const char *str);

int		ft_check_lst(t_data *data);

int		ft_type_set_path(t_data *data);
int		ft_type_set_cmd(t_data *data);

char	*ft_expansion_get_str(t_data *data, const char *str);
int		ft_expansion(t_data *data);
int		ft_expansion_str(t_data *data, const char *str, char **new_str);
int		ft_expansion_is_word(const char *str);
int		ft_expansion_join_var(t_data *data,
			const char *str, char **buffer, size_t *i);
t_list	*ft_expansion_split_node_content(const char *str);
int		ft_expansion_is_multie_arg(const char *str);
int		ft_expansion_split_node(t_data *data, t_list **lst, t_list *last);
int		ft_expantion_get_while(t_data *data,
			const char *str, size_t *i, char **buffer);
char	*ft_expansion_get_str_func(t_data *data, const char *str,
			int (*get_while)(t_data *, const char *, size_t *, char **));
int		ft_expansion_add_car(char *str, int car, char **buffer);

void	ft_quotes_remove(char *str);
int		ft_quotes_rm_rf(t_data *data);

#endif
