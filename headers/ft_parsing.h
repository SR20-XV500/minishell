/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:21:58 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/12 01:35:04 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSING_H
# define FT_PARSING_H

# include "ft_env.h"

# define PARSER_WORD 12
# define PARSER_NO_WORD 13

enum e_delemitor
{
	D_PIPE,
	D_HEREDOC,
	D_INTPUT,
	D_OUTPUT_APEND,
	D_OUTPUT,
	D_QUOTE,
	D_NOT_SET
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

#endif