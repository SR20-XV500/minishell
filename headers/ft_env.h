/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:47:44 by tlassere          #+#    #+#             */
/*   Updated: 2024/01/31 13:29:02 by tlassere         ###   ########.fr       */
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

typedef struct s_env
{
	char	**envp;
	char	*path;
}	t_env;

void	ft_env_free(t_env *env);
char	*ft_env_get_content(t_env env, const char *name);
int		ft_env_check(t_env *env);
int		ft_env_get_pos(t_env env, const char *name);
int		ft_env_update(t_env *env, const char *name, char *all_str);
t_env	ft_env_init(const char **envp);

#endif