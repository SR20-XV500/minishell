/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:55:10 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/21 21:31:37 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
