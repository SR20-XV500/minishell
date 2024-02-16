/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:21:58 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/16 19:32:01 by tlassere         ###   ########.fr       */
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
# define PARSER_

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

typedef struct s_word
{
	char	*word;
	int		type;
}	t_word;

typedef struct s_data
{
	t_env	*env;
	t_list	*words;
}	t_data;

t_data	*ft_data_get(const char **envp);
void	ft_data_free(t_data **data);

void	ft_word_lst_clear(t_data *data);
void	ft_word_free(void *data);
int		ft_word_add(t_data *data, const char *str, int type);
t_list	*ft_word_lst_make(const char *str, int type);

int		ft_parser(t_data *data, const char *str);
int		ft_parser_use_line(t_data *data, const char *str);

int		ft_check_lst(t_data *data);

int		ft_type_set_path(t_data *data);
int		ft_type_set_cmd(t_data *data);

int		ft_expansion(t_data *data);
int		ft_expansion_str(const char *str, char **new_str);
int		ft_expansion_is_word(const char *str);

#endif
