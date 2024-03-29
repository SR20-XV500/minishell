/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:55:10 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/10 15:09:34 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_here_doc(t_list ***here_doc)
{
	size_t	index;

	index = 0;
	if (here_doc && *here_doc)
	{
		while ((*here_doc)[index])
		{
			ft_lstclear(*here_doc + index, &ft_word_free);
			index++;
		}
		free(*here_doc);
		*here_doc = NULL;
	}
}

void	ft_data_free(t_data **data)
{
	if (data && *data)
	{
		if ((*data)->env)
		{
			ft_env_free((*data)->env);
			(*data)->env = NULL;
		}
		if ((*data)->words)
			ft_word_lst_clear(*data);
		ft_data_clear_fd(*data);
		if ((*data)->children)
			free((*data)->children);
		if ((*data)->here_doc)
			ft_free_here_doc(&((*data)->here_doc));
		ft_tab_free((*data)->tabs_lines);
		free(*data);
		*data = NULL;
	}
}

static t_data	*ft_data_make(const char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data)
	{
		ft_bzero(data, sizeof(t_data));
		data->exit_program = FAIL;
		data->env = ft_env_init(envp);
		if (data->env == NULL)
			ft_data_free(&data);
	}
	return (data);
}

static void	ft_data_set_redirect(t_data *data)
{
	if (data)
	{
		data->input_fd = STDIN;
		data->output_fd = STDOUT;
	}
}

t_data	*ft_data_get(const char **envp)
{
	t_data	*data;

	data = NULL;
	if (envp)
	{
		data = ft_data_make(envp);
		ft_data_set_redirect(data);
	}
	return (data);
}
