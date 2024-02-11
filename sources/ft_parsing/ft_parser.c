/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:14:15 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/11 19:10:14 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser_add_delimitor(t_data *data, const char *str, size_t *i)
{
	int	exit_status;

	exit_status = D_NOT_SET;
	if (ft_strcmp_s2(str, ">>") == CMP_EGAL)
	{
		exit_status = ft_word_add(data, ">>", D_OUTPUT_APEND);
		(*i)++;
	}
	else if (ft_strcmp_s2(str, "<<") == CMP_EGAL)
	{
		exit_status = ft_word_add(data, "<<", D_HEREDOC);
		(*i)++;
	}
	else if (ft_strcmp_s2(str, "|") == CMP_EGAL)
		exit_status = ft_word_add(data, "|", D_PIPE);
	else if (ft_strcmp_s2(str, "<") == CMP_EGAL)
		exit_status = ft_word_add(data, "<", D_INTPUT);
	else if (ft_strcmp_s2(str, ">") == CMP_EGAL)
		exit_status = ft_word_add(data, ">", D_OUTPUT);
	else if (ft_strcmp_s2(str, "\"") == CMP_EGAL
		|| ft_strcmp_s2(str, "\'") == CMP_EGAL)
		exit_status = D_QUOTE;
	return (exit_status);
}

//static int	ft_parse_use_line(t_data *data, const char *str)
//{
//	int		ret;
//	int		buffer;
//	size_t	i;

//	ret = SUCCESS;
//	i = 0;
//	while (str[i] && ret == SUCCESS)
//	{
//		buffer = ft_ge
//		i++;
//	}
//	return (ret);
//}

//int	ft_parse(t_data *data, const char *str)
//{
//	int	ret;

//	ret = BAD_PARAMETER;
//	if (data && str)
//	{
//		ret = ;
//	}
//	return (ret);
//}
