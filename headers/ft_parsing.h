/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:21:58 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/10 16:08:29 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSING_H
# define FT_PARSING_H

# define PARSER_WORD 12
# define PARSER_NO_WORD 13
# define PARSER_ERR_OP_NEWLINE 1
# define PARSER_NEAR_PIPE 2
# define PARSER_EXPANSION_VAR_CHANGE 14
# define PARSER_EXPANSION_VAR_NO_CHANGE 15
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

int		ft_parser(t_data *data, const char *str);
int		ft_parser_use_line(t_data *data, const char *str);

int		ft_check_lst(t_data *data);

int		ft_type_set_path(t_data *data);
int		ft_type_set_cmd(t_data *data);

int		ft_expansion(t_data *data);
char	*ft_expansion_get_str(t_data *data, const char *str);
int		ft_expansion_str(t_data *data, const char *str, char **new_str);
int		ft_expansion_is_word(const char *str);
int		ft_expansion_join_var(t_data *data,
			const char *str, char **buffer, size_t *i);
t_list	*ft_expansion_split_node_content(const char *str);
int		ft_expansion_is_multi_arg(const char *str);
int		ft_expansion_split_node(t_data *data, t_list **lst, t_list *last);
int		ft_expantion_get_while(t_data *data,
			const char *str, size_t *i, char **buffer);
char	*ft_expansion_get_str_func(t_data *data, const char *str,
			int (*get_while)(t_data *, const char *, size_t *, char **));
int		ft_expansion_add_car(char *str, int car, char **buffer);

int		ft_quotes_remove(char *str);
int		ft_quotes_rm_rf(t_data *data);

#endif
