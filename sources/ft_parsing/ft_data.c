/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:55:10 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/25 20:53:05 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_here_doc(t_list **here_doc)
{
	size_t	index;

	index = 0;
	while (here_doc[index])
	{
		ft_lstclear(here_doc + index, &ft_word_free);
		index++;
	}
	free(here_doc);
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
		if ((*data)->input_fd > 2)
			close((*data)->input_fd);
		if ((*data)->output_fd > 2)
			close((*data)->output_fd);
		if ((*data)->dup_std[STDIN] > 2)
			close((*data)->dup_std[STDIN]);
		if ((*data)->dup_std[STDOUT] > 2)
			close((*data)->dup_std[STDOUT]);
		if ((*data)->children)
			free((*data)->children);
		if ((*data)->here_doc)
			ft_free_here_doc((*data)->here_doc);
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
		data->env = ft_env_init(envp);
		if (data->env)
			ft_pwd_init(&data->env->pwd);
		else
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
