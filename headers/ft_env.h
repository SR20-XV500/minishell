/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:47:44 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/01 23:06:10 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# define D_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define ENV_SUCCESS 0
# define ENV_FAIL 1
# define ENV_UPDATE_SUCCESS 0
# define ENV_UPDATE_FAIL 1
# define ENV_UPDATE_NONE 2
# define ENV_EXISTING_VARIABLE 3
# define ENV_NOT_EXISTING_VARIABLE 4
# define ENV_BAD_PARAMETER 5

typedef struct s_env
{
	char	**envp;
	char	*path;
}	t_env;

void	ft_env_free(t_env *env);
char	*ft_env_get_content(t_env env, const char *name);
char	*ft_env_get_name(const char *all_str);
int		ft_env_check(t_env *env);
int		ft_env_get_pos(t_env env, const char *name);
int		ft_env_update(t_env *env, const char *name, const char *all_str);
int		ft_env_add(t_env *env, const char *all_str);
int		ft_env_del(t_env *env, const char *name);
t_env	ft_env_init(const char **envp);

#endif