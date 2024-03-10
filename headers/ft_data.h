/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:15:04 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/10 15:08:54 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DATA_H
# define FT_DATA_H

typedef struct s_word
{
	char	*word;
	int		type;
}			t_word;

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
void		ft_data_clear_fd(t_data *data);

int			ft_word_add(t_data *data, const char *str, int type);
void		ft_word_free(void *data);
t_list		*ft_word_lst_make(const char *str, int type);
int			ft_word_lst_add(t_list **lst_el, const char *str, int type);
void		ft_word_lst_clear(t_data *data);

#endif
