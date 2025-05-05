/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:53:49 by tlassere          #+#    #+#             */
/*   Updated: 2025/05/06 00:03:57 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expansion_is_word(const char *str)
{
	if (*str == '$' && (ft_isalpha(*(str + 1)) || *(str + 1) == '_'
		|| *(str + 1) == '?'))
		return (TRUE);
	return (FALSE);
}

int	ft_expansion(t_data *data)
{
	int	status;

	status = BAD_PARAMETER;
	if (data)
	{
		status = SUCCESS;
	}
	return (status);
}
