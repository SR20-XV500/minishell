/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:13:28 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/20 02:21:05 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXEC_H
# define FT_EXEC_H

# include "ft_parsing.h"
# define REDIRECT_AMBIGUOUS_REDIRECT 26
# define ERR_SUCH_FILE "minishell: %s: No such file or directory\n"
# define ERR_AMBIGUOUS_REDIRECT "minishell: %s: ambiguous redirect\n"

char	*ft_redirect_get_path(t_data *data, const char *str);
int		ft_exec(t_data *data);
int		ft_exec_redirect_fd(t_data *data, int type,
	const char *path, const char *err_str);

#endif
