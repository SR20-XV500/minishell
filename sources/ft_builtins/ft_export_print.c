/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:27:00 by bcheronn          #+#    #+#             */
/*   Updated: 2024/03/02 00:48:12 by bcheronn         ###   ########.fr       */
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

static void	ft_swap_strings(char **a, char **b)
{
	char	*t;

	t = *a;
	*a = *b;
	*b = t;
}

int	ft_partition(char **array, int lower_index, int higher_index)
{
	int	pivot;
	int	i;
	int	j;

	pivot = higher_index;
	i = lower_index - 1;
	j = lower_index;
	while (j < higher_index)
	{
		if (ft_strcmp_s2(array[j], array[pivot]) < 0)
		{
			i++;
			ft_swap_strings(&array[i], &array[j]);
		}
		j++;
	}
	ft_swap_strings(&array[i + 1], &array[higher_index]);
	return (i + 1);
}

static void	ft_strings_quicksort(char **array, int lower_index,
		int higher_index)
{
	int	pivot;

	if (lower_index < higher_index)
	{
		pivot = ft_partition(array, lower_index, higher_index);
		ft_strings_quicksort(array, lower_index, pivot - 1);
		ft_strings_quicksort(array, pivot + 1, higher_index);
	}
}

// TODO: Print the tab
// while (*env->envp)
// {
// 	ft_printf("declare -x %s=\"%s\"\n", ft_env_get_name(*env->envp),
// 		ft_env_get_content(*env, ft_env_get_name(*env->envp)));
// 	++env->envp;
// }
int	ft_export_print(t_env *env)
{
	int		exit_code;
	char	**export;

	exit_code = MALLOC_FAIL;
	if (env)
	{
		export = ft_tabjoin(env->envp, env->export);
		if (export)
		{
			ft_strings_quicksort(export, 0, ft_tab_len(export) - 1);
			exit_code = ft_env((const char **)export);
			free(export);
		}
	}
	return (exit_code);
}
