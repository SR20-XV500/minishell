/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:27:00 by bcheronn          #+#    #+#             */
/*   Updated: 2024/03/02 20:18:58 by bcheronn         ###   ########.fr       */
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
	new_tab = malloc((new_tab_len + 1) * sizeof(char *));
	if (new_tab)
	{
		ft_memmove(new_tab, t1, t1_len * sizeof(char *));
		ft_memmove(new_tab + t1_len, t2, t2_len * sizeof(char *));
		new_tab[new_tab_len] = NULL;
	}
	return (new_tab);
}

static int	ft_export_print_line(char **export, const char *var)
{
	int		ret;
	char	*name;
	char	*value;

	ret = FAIL;
	name = ft_env_get_name(var);
	value = ft_env_tab_get_content(export, name);
	if (ft_strchr(var, '='))
		ret = ft_printf("declare -x %s=\"%s\"\n", name, value);
	else
		ret = ft_printf("declare -x %s\n", name);
	if (name)
		free(name);
	if (value)
		free(value);
	return (ret);
}

int	ft_export_print(t_env *env)
{
	int		exit_code;
	char	**export;
	char	**tmp;

	exit_code = MALLOC_FAIL;
	if (env)
	{
		export = ft_tabjoin(env->envp, env->export);
		if (export)
		{
			exit_code = SUCCESS;
			ft_strings_quicksort(export, 0, ft_tab_len(export) - 1);
			tmp = export;
			while (*tmp && exit_code != MALLOC_FAIL)
				exit_code = ft_export_print_line(export, *tmp++);
			free(export);
		}
	}
	return (exit_code);
}
