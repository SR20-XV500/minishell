/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:47:44 by tlassere          #+#    #+#             */
/*   Updated: 2024/01/30 20:58:44 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# define D_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define ENV_SUCCESS 0
# define ENV_FAIL 1

typedef struct s_env
{
	char	**envp;
	char	*path;
}	t_env;

void	ft_env_free(t_env *env);
char	*ft_env_get_content(t_env env, char *str);
int		ft_env_check(t_env *env);
int		ft_env_get_pos(t_env env, char *str);
t_env	ft_env_init(char **envp);

#endif