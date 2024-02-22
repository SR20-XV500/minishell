/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:29:02 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/22 14:02:20 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTINS_H
# define FT_BUILTINS_H

# define IS_ARG 0
# define IS_NOT_ARG 1
# define PWD_GET 0
# define PWD_CHANGE_CONTENT 1
# define PWD_INIT 2
# define CD_TO_MANY_ARGS 3
# define CD_HOME_NOT_SET 4
# define CD_OLDPWD_NOT_SET 5
# define CD_INVALID_PATH -1
# define CD_VALID_PATH 1

int	ft_echo(char **argv, char **envp);

int	ft_pwd(char **argv, char **envp);

int	ft_cd(char **argv, char **envp);

int	ft_unset(char **argv, t_env *env);

int	ft_export(char **argv, char **envp);

#endif
