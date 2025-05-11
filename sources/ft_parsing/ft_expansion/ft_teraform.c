/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_teraform.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:44:23 by tlassere          #+#    #+#             */
/*   Updated: 2025/05/11 15:46:18 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_token(char *str)
{
	size_t	i;

	i = 1;
	if (str[i] != '?')
	{
		while (ft_isalpha(str[i]) || str[i] == '_')
			i++;
	}
	else
		i = 2;
	return (ft_substr(str, 0, i));
}

static int	ft_set_terraform(t_teraform *teraform, char *begin_str, char *str)
{
	size_t	blen;

	if (begin_str != str)
	{
		teraform->left = ft_substr(begin_str, 0, str - begin_str);
		if (teraform->left == NULL)
			return (FAIL);
	}
	teraform->token = ft_get_token(str);
	if (teraform->token == NULL)
		return (FAIL);
	blen = strlen(teraform->token);
	if (str[blen])
	{
		teraform->right = ft_substr(str + blen, 0, ft_strlen(str + blen));
		if (teraform->right == NULL)
			return (FAIL);
	}
	return (SUCCESS);
}

static int	ft_set_expand(t_teraform *teraform, t_data *data)
{
	char	*buffer;

	buffer = ft_research_token(teraform->token, data);
	if (ft_strlen(buffer) >= 1)
	{
		if (ft_strchr("\t\v\n\r ", buffer[0]))
			teraform->ljoin = FALSE;
		if (ft_strchr("\t\v\n\r ", buffer[ft_strlen(buffer) - 1]))
			teraform->rjoin = FALSE;
	}
	if (teraform->inquote || buffer == NULL)
	{
		teraform->sp = malloc(sizeof(char *) * 2);
		if (!teraform->sp)
			return (free(buffer), FAIL);
		teraform->sp[0] = buffer;
		teraform->sp[1] = NULL;
	}
	else
		teraform->sp = the_mastermind(buffer);
	if (!teraform->sp)
		return (FAIL);
	return (SUCCESS);
}

static void	ft_free_teraform(t_teraform *teraform)
{
	if (teraform->left)
		free(teraform->left);
	if (teraform->right)
		free(teraform->right);
	if (teraform->token)
		free(teraform->token);
	if (teraform->sp)
		ft_tab_free(teraform->sp);
}

char	*ft_expend_teraform(t_data *data, t_list **lst, char *str, int inquote)
{
	t_teraform	teraform;
	char		*ret;

	ft_bzero(&teraform, sizeof(t_teraform));
	teraform.inquote = inquote;
	teraform.rjoin = TRUE;
	teraform.ljoin = TRUE;
	ret = str;
	if (ft_set_terraform(&teraform,
			((t_word *)(*lst)->content)->word, str) == SUCCESS
			&& ft_set_expand(&teraform, data) == SUCCESS)
		ret = join_expand(lst, &teraform, str);
	ft_free_teraform(&teraform);
	return (ret);
}
