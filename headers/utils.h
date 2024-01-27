/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:05:05 by tlassere          #+#    #+#             */
/*   Updated: 2024/01/27 02:15:10 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <readline/readline.h>
# include <readline/history.h>

void	ft_check_args_main(int argc);
char	**ft_get_line(void);
void	ft_use_line(void);

#endif