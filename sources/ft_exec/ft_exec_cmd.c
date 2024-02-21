/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:46:19 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/21 20:55:20 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	ft_exec_cmd_arg_get_len(t_list *lst)
{
	unsigned int	len;

	len = 0;
	if (lst)
	{
		len = 2;
		while (lst && ((t_word *)lst->content)->type != D_PIPE)
		{
			if (((t_word *)lst->content)->type == TY_ARG)
				len++;
			lst = lst->next;
		}
	}
	return (len);
}

static char	**ft_exec_cmd_set_argv(t_list *lst,
	char **argv, unsigned int len)
{
	unsigned int	index;

	index = 1;
	if (lst && len > 1 && argv && *argv)
	{
		len--;
		while (lst && ((t_word *)lst->content)->type != D_PIPE
			&& index < len && argv)
		{
			if (((t_word *)lst->content)->type == TY_ARG)
			{
				argv[index] = ft_strdup(((t_word *)lst->content)->word);
				if (argv[index] == NULL)
				{
					ft_tab_free(argv);
					argv = NULL;
				}
				index++;
			}
			lst = lst->next;
		}
	}
	return (argv);
}

static char	**ft_exec_cmd_set_first_arg(t_list *lst,
	char **argv, unsigned int len)
{
	if (lst && len > 1 && ((t_word *)lst->content)->type == TY_CMD)
	{
		argv[0] = ft_strdup(((t_word *)lst->content)->word);
		if (argv[0] == NULL)
		{
			ft_tab_free(argv);
			argv = NULL;
		}
	}
	return (argv);
}

static char	**ft_exec_cmd_get_argv(t_list *lst)
{
	char			**argv;
	unsigned int	len;

	argv = NULL;
	if (lst)
	{
		len = ft_exec_cmd_arg_get_len(lst);
		if (len)
		{
			argv = malloc(len * sizeof(char **));
			if (argv)
			{
				ft_bzero(argv, len * sizeof(char **));
				argv = ft_exec_cmd_set_first_arg(lst, argv, len);
				argv = ft_exec_cmd_set_argv(lst, argv, len);
			}
		}
	}
	return (argv);
}

//printf("hello le path : %s\n", cmd_content.path);
//ft_printf("argument:\n-----\n%w-----\n", cmd_content.argv);
//ft_printf("environement:\n-----\n%w-----\n", cmd_content.envp);

int	ft_exec_cmd(t_data *data, t_list *lst)
{
	int				status;
	t_cmd_content	cmd_content;

	status = BAD_PARAMETER;
	ft_bzero(&cmd_content, sizeof(t_cmd_content));
	if (data && lst && lst->content)
	{
		status = SUCCESS;
		if (((t_word *)lst->content)->type == TY_CMD)
		{
			cmd_content.path = ft_exec_cmd_get_path(data,
					((t_word *)lst->content)->word);
			cmd_content.argv = ft_exec_cmd_get_argv(lst);
			cmd_content.envp = ft_tab_dump(data->env->envp);
			status = ft_exec_cmd_true(data, cmd_content);
		}
		else if (((t_word *)lst->content)->type == D_PIPE)
			status = D_PIPE;
		ft_exec_cmd_free(cmd_content);
	}
	return (status);
}
