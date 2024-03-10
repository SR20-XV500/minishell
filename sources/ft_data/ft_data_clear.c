/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:02:56 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/10 15:11:08 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_data_clear_fd(t_data *data)
{
	if (data)
	{
		if (data->output_fd > STDERR)
		{
			close(data->output_fd);
			data->output_fd = STDOUT;
		}
		if (data->input_fd > STDERR)
		{
			close(data->input_fd);
			data->output_fd = STDIN;
		}
		if (data->dup_std[STDIN] > STDERR)
		{
			close(data->dup_std[STDIN]);
			data->dup_std[STDIN] = STDIN;
		}
		if (data->dup_std[STDOUT] > 2)
		{
			close(data->dup_std[STDOUT]);
			data->dup_std[STDOUT] = STDOUT;
		}
	}
}
