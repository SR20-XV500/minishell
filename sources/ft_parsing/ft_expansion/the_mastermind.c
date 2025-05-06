/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:54:21 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/21 12:49:12 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_seg(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_strchr("\n\t\v\r ", s[i]) == NULL)
		i++;
	return (i);
}

static size_t	ft_count_seg(const char *s)
{
	size_t	segs;
	size_t	i;

	i = 0;
	segs = 0;
	while (s[i])
	{
		if (ft_get_seg(s + i))
		{
			i += ft_get_seg(s + i);
			segs++;
		}
		else
			i++;
	}
	return (segs);
}

static void	ft_free_bad_memorie(char **strs, size_t n)
{
	size_t	i;

	i = 0;
	while (i <= n)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char	**ft_insert_segments(char const *s, char **strs)
{
	size_t	segs;
	size_t	i;
	size_t	cur_seg;

	i = 0;
	segs = 0;
	while (s[i])
	{
		cur_seg = ft_get_seg(s + i);
		if (cur_seg)
		{
			strs[segs] = ft_substr(s, i, ft_get_seg(s + i));
			if (strs[segs] == NULL)
			{
				ft_free_bad_memorie(strs, segs);
				return (NULL);
			}
			i += ft_get_seg(s + i);
			segs++;
		}
		else
			i++;
	}
	return (strs);
}

char	**the_mastermind(char *token_split)
{
	char	**strs;
	size_t	segments;

	segments = ft_count_seg(token_split);
	strs = (char **)malloc((segments + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	strs[segments] = NULL;
	strs = ft_insert_segments(token_split, strs);
	free(token_split);
	return (strs);
}
