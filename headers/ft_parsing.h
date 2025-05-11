/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:21:58 by tlassere          #+#    #+#             */
/*   Updated: 2025/05/11 14:39:27 by tlassere         ###   ########.fr       */
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
	TY_NOEXPENDED,
	TY_DELIM_HEREDOC
};

enum e_heredoc
{
	HER_STR = 90,
	HER_EOF
};

typedef struct s_teraform
{
	char	*left;
	char	*right;
	char	*token;
	char	**sp;
	int		ljoin;
	int		rjoin;
	int		inquote;
	size_t	rlen;
}	t_teraform;

int		ft_parser(t_data *data, const char *str);
int		ft_parser_use_line(t_data *data, const char *str);

int		ft_check_lst(t_data *data);

int		ft_type_set_path(t_data *data);
int		ft_type_set_cmd(t_data *data);

int		ft_expansion(t_data *data);
char	*ft_expend_teraform(t_data *data, t_list **lst, char *str, int inquote);
int		ft_expansion_is_word(const char *str);
char	**the_mastermind(char *token_split);

int		ft_quotes_remove(char *str);

t_list	*ft_word_lst_make_join(char *str, int type);
void	ft_words_clear(t_list **begin);
void	ft_remove_caracter(char *str);
char	*ft_research_token(char *token, t_data *data);
void	join_add_node(t_list **begin, t_list *add);
int		join_create_set_node(t_list **begin, char *buffer, int type);
char	*join_expand(t_list **lst, t_teraform *teraform, char *str);
void	ft_while_del_node(t_data *data);

#endif
