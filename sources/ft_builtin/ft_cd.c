/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:09:37 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/09 20:06:14 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_display_prompt(int status, char *path)
{
	if (status == CD_TO_MANY_ARGS)
		ft_fprintf(STDERR, "minishell: cd: HOME not set");
	if (status == CD_HOME_NOT_SET)
		ft_fprintf(STDERR, "minishell: cd: too many arguments");
	if (status == CD_INVALID_PATH && path)
	{
		ft_printf("minishell: cd: ");
		perror(path);
	}
}

static int	ft_check_args(char **argv, char **envp, int *exit_code)
{
	int	ret;
	int	arg_len;

	ret = FAIL;
	if (argv)
	{
		ret = SUCCESS;
		arg_len = ft_tab_len(argv);
		if (arg_len > 2)
			ret = CD_TO_MANY_ARGS;
		if ((arg_len == 1 || (arg_len == 2 && argv[1][0] == '~'))
			&& ft_env_tab_get_pos(envp, "HOME") == -1)
			ret = CD_HOME_NOT_SET;
	}
	if (ret != SUCCESS)
	{
		*exit_code = 1;
		ft_display_prompt(ret, NULL);
	}
	return (ret);
}

static int	ft_exec_path(char *path)
{
	int	ret;

	ret = CD_INVALID_PATH;
	if (path && chdir(path) != -1)
		ret = CD_VALID_PATH;
	return (ret);
}

char	*ft_get_path(char **argv, char **envp, char **used_path)
{
	char	*path;

	path = NULL;
	if (ft_tab_len(argv) == 1)
	{
		path = ft_env_tab_get_content(envp, "HOME");
		*used_path = ft_strdup(path);
	}
	else
	{
		if (argv[1][0] == '/')
			path = ft_strdup(argv[1]);
		else
			path = ft_path_parser(ft_pwd_get(), argv[1]);
		*used_path = ft_strdup(argv[1]);
	}
	return (path);
}

int	ft_cd(char **argv, char **envp)
{
	int		exit_code;
	char	*new_path;
	char	*used_path;

	exit_code = MALLOC_FAIL;
	new_path = NULL;
	used_path = NULL;
	if (ft_check_args(argv, envp, &exit_code) == SUCCESS)
	{
		new_path = ft_get_path(argv, envp, &used_path);
		if (new_path)
			exit_code = ft_exec_path(new_path);
		if (exit_code == CD_INVALID_PATH)
		{
			ft_display_prompt(exit_code, used_path);
			free(new_path);
		}
		else
			ft_pwd_change_content(new_path);
		if (used_path)
			free(used_path);
	}
	return (exit_code);
}
