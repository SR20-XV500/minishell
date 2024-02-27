/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:27:00 by bcheronn          #+#    #+#             */
/*   Updated: 2024/02/27 01:55:18 by bcheronn         ###   ########.fr       */
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

// TODO: bash: export: `1toto': not a valid identifier
// TODO: refactor ft_display_prompt?

// TODO: export VAR:
// Check if var is a valid name
// Check if var contains an =
// * If not check if it is in **envp
// ** If not add it to **export
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
	if (ft_export_is_valid(arg))
		ret = SUCCESS;
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
