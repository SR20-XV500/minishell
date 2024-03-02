/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:27:00 by bcheronn          #+#    #+#             */
/*   Updated: 2024/03/02 18:09:10 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_swap_strings(char **a, char **b)
{
	char	*t;

	t = *a;
	*a = *b;
	*b = t;
}

static int	ft_partition(char **array, int lower_index, int higher_index)
{
	int	pivot;
	int	i;
	int	j;

	pivot = higher_index;
	i = lower_index - 1;
	j = lower_index;
	while (j < higher_index)
	{
		if (ft_strcmp_s2(array[j], array[pivot]) < 0)
		{
			i++;
			ft_swap_strings(&array[i], &array[j]);
		}
		j++;
	}
	ft_swap_strings(&array[i + 1], &array[higher_index]);
	return (i + 1);
}

void	ft_strings_quicksort(char **array, int lower_index, int higher_index)
{
	int	pivot;

	if (lower_index < higher_index)
	{
		pivot = ft_partition(array, lower_index, higher_index);
		ft_strings_quicksort(array, lower_index, pivot - 1);
		ft_strings_quicksort(array, pivot + 1, higher_index);
	}
}
