/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:55:10 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/10 23:56:59 by tlassere         ###   ########.fr       */
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

t_data *ft_data_get(char *str, const char **envp)
{
	t_data	*data;

	data = NULL;
	if (str && envp)
	{
		data = ft_data_make(envp);
	}
	return (data);
}
