/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:27:00 by bcheronn          #+#    #+#             */
/*   Updated: 2024/02/28 01:02:44 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_export_is_valid(const char *name)
{
	int	ret;

	ret = FALSE;
	if (name && *name)
	{
		if (*name == '_' || ft_isalpha(*name))
		{
			name++;
			ret = TRUE;
			while (*name && ret)
			{
				if (*name != '_' && !ft_isalnum(*name))
					ret = FALSE;
				name++;
			}
		}
	}
	return (ret);
}

// TODO: allocate *export to NULL at init
// TODO: export VAR:
// Check if var contains an =
// * If not check if it is in **envp
// ** If not add it to **export
// ** If yes do nothing
// * If yes check if it exist in **export
// ** If yes remove it from **export and add it to **envp
// ** If not check if it exists in **envp
// *** If not add it to **envp
// *** If yes update it in **envp
static int	ft_export_process(char *arg, t_env *env)
{
	int	ret;

	(void)env;
	ret = FAIL;
	if (ft_export_is_valid(ft_env_get_name(arg)))
	{
		if (ft_strchr(arg, '='))
			ret = SUCCESS;
		else
		{
			if (ft_env_tab_get_pos(env->envp, arg) == -1)
				ret = ft_env_tab_add(&env->export, arg);
			ret = SUCCESS;
		}
	}
	else
		ft_fprintf(STDERR, "minishell: export: `%s': not a valid identifier\n",
			arg);
	return (ret);
}

int	ft_export(char **argv, t_env *env)
{
	int	exit_code;

	exit_code = FAIL;
	if (env)
	{
		if (argv && argv[0] && argv[1])
		{
			argv++;
			exit_code = SUCCESS;
			while (argv[0])
			{
				if (ft_export_process(argv[0], env) == FAIL)
					exit_code = FAIL;
				argv++;
			}
		}
		else
			exit_code = ft_export_print(env);
	}
	return (exit_code);
}
