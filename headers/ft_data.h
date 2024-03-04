/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:15:04 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/04 13:05:10 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DATA_H
# define FT_DATA_H

typedef struct s_word
{
	char	*word;
	int		type;
}			t_word;

//* TODO: Refactor input_fd/output_fd
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
}			t_data;

t_data		*ft_data_get(const char **envp);
void		ft_data_free(t_data **data);
void		ft_free_here_doc(t_list ***here_doc);

int			ft_word_add(t_data *data, const char *str, int type);
void		ft_word_free(void *data);
t_list		*ft_word_lst_make(const char *str, int type);
int			ft_word_lst_add(t_list **lst_el, const char *str, int type);
void		ft_word_lst_clear(t_data *data);

#endif
