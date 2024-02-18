/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:39:20 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/18 15:05:43 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_expansion_split_node_content(const char *str)
{
	t_list	*lst;

	lst = NULL;
	if (str)
	{
	}
	return (lst);
}

int	ft_expansion_is_multie_arg(const char *str)
{
	int		status;
	char	*cpy_ptr;

	status = BAD_PARAMETER;
	cpy_ptr = (char *)str;
	if (str)
	{
		status = FAIL;
		while (*cpy_ptr && status == FAIL)
		{
			if (*cpy_ptr == '\"' && ft_strchr(cpy_ptr + 1, '\"'))
				cpy_ptr = ft_strchr(cpy_ptr + 1, '\"');
			if (*cpy_ptr == '\'' && ft_strchr(cpy_ptr + 1, '\''))
				cpy_ptr = ft_strchr(cpy_ptr + 1, '\'');
			if (ft_strchr(" \t\v\r\n\f", *cpy_ptr))
				status = SUCCESS;
			cpy_ptr++;
		}
	}
	return (status);
}
