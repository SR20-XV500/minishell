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

static size_t	ft_get_seg(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	ft_count_seg(const char *s, char c)
{
	size_t	segs;
	size_t	i;

	i = 0;
	segs = 0;
	while (s[i])
	{
		if (ft_get_seg(s + i, c))
		{
			i += ft_get_seg(s + i, c);
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

static char	**ft_insert_segments(char const *s, char c, char **strs)
{
	size_t	segs;
	size_t	i;
	size_t	cur_seg;

	i = 0;
	segs = 0;
	while (s[i])
	{
		cur_seg = ft_get_seg(s + i, c);
		if (cur_seg)
		{
			strs[segs] = ft_substr(s, i, ft_get_seg(s + i, c));
			if (strs[segs] == NULL)
			{
				ft_free_bad_memorie(strs, segs);
				return (NULL);
			}
			i += ft_get_seg(s + i, c);
			segs++;
		}
		else
			i++;
	}
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	segments;

	if (!s)
		return (NULL);
	segments = ft_count_seg(s, c);
	strs = (char **)malloc((segments + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	strs[segments] = NULL;
	return (ft_insert_segments(s, c, strs));
}
