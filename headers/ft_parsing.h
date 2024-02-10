/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:21:58 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/10 23:56:06 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSING_H
# define FT_PARSING_H

# include "ft_env.h"

typedef struct s_data
{
	t_env	*env;
}	t_data;

t_data	*ft_data_get(char *str, const char **envp);
void	ft_data_free(t_data **data);

#endif