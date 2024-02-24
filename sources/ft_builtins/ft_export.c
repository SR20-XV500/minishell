/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:27:00 by bcheronn          #+#    #+#             */
/*   Updated: 2024/02/24 20:06:46 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_tabjoin(char **t1, char **t2)
{
	char	**new_tab;
	int		new_tab_len;
	int		t1_len;
	int		t2_len;

	t1_len = ft_tab_len(t1);
	if (t1_len == -1)
		t1_len = 0;
	t2_len = ft_tab_len(t2);
	if (t2_len == -1)
		t2_len = 0;
	new_tab_len = t1_len + t2_len;
	new_tab = malloc((new_tab_len + 1) * sizeof(*new_tab));
	if (new_tab)
	{
		ft_memmove(new_tab, t1, t1_len * sizeof(*t1));
		ft_memmove(new_tab + t1_len, t2, t2_len * sizeof(*t2));
		new_tab[new_tab_len] = NULL;
	}
	return (new_tab);
}

// TODO: Sort the tab
// TODO: Print the tab
// while (*env->envp)
// {
// 	ft_printf("declare -x %s=\"%s\"\n", ft_env_get_name(*env->envp),
// 		ft_env_get_content(*env, ft_env_get_name(*env->envp)));
// 	++env->envp;
// }
static int	ft_export_print(t_env *env)
{
	int		exit_code;
	char	**export;

	exit_code = FAIL;
	if (env)
	{
		export = ft_tabjoin(env->envp, env->export);
		if (export)
		{
			ft_env((const char **)export);
			free(export);
			exit_code = SUCCESS;
		}
	}
	return (exit_code);
}

int	ft_export(char **argv, t_env *env)
{
	int	exit_code;

	exit_code = FAIL;
	if (env)
	{
		if (argv && argv[0] && argv[1])
		{
			ft_printf("args -> parse and add or update\n");
			exit_code = SUCCESS;
		}
		else
			exit_code = ft_export_print(env);
	}
	return (exit_code);
}
