/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_initial_shlvl.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:11:17 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/03 17:25:13 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_shlvl_syntax(const char *str)
{
	int		ret;
	char	*str_trim;
	size_t	i;

	ret = MALLOC_FAIL;
	str_trim = ft_strtrim(str, "\n\v\t\f\r ");
	i = 0;
	if (str_trim)
	{
		ret = ENV_FAIL;
		if (str_trim[0] == '-' || str_trim[0] == '+')
			i++;
		while (str_trim[i] >= '0' && str_trim[i] <= '9')
			i++;
		if (str_trim[i] == '\0')
			ret = ENV_SUCCESS;
		free(str_trim);
	}
	return (ret);
}

static long long	ft_env_shlvl_succes(const char *buffer)
{
	long long	value;

	value = ft_atoll(buffer);
	if (value >= 0 && value < 999)
		value++;
	else if (ft_check_overflow(buffer, value) == OVERFLOW)
		value = 1;
	else if (value >= 999 && value < INT_MAX)
	{
		ft_fprintf(2, W_SH, value);
		value = 1;
	}
	else if (value < 0)
		value = 0;
	return (value);
}

static int	ft_env_update_shlvl(t_env *env, long long value)
{
	char	*buffer;
	char	*join;
	int		ret;

	buffer = ft_itoa((int)value);
	ret = MALLOC_FAIL;
	if (buffer)
	{
		join = ft_strjoin("SHLVL=", buffer);
		if (join)
		{
			ret = ENV_SUCCESS;
			ft_env_update(env, "SHLVL", join);
			free(join);
		}
		free(buffer);
	}
	return (ret);
}

static int	ft_env_init_shlvl_update(t_env *env)
{
	int			ret;
	char		*buffer;
	long long	value;

	ret = MALLOC_FAIL;
	buffer = ft_env_get_content(*env, "SHLVL");
	value = 0;
	if (buffer)
	{
		ret = ft_shlvl_syntax(buffer);
		if (ret == ENV_FAIL)
			value = 1;
		else if (ret == ENV_SUCCESS)
			value = ft_env_shlvl_succes(buffer);
		if (ret != MALLOC_FAIL)
			ret = ft_env_update_shlvl(env, value);
		free(buffer);
	}
	return (ret);
}

int	ft_env_init_shlvl(t_env *env)
{
	int		ret;

	ret = MALLOC_FAIL;
	if (ft_env_get_pos(*env, "SHLVL") != -1)
		ret = ft_env_init_shlvl_update(env);
	else
	{
		if (ft_env_add(env, "SHLVL=1") != MALLOC_FAIL)
			ret = ENV_SUCCESS;
	}
	return (ret);
}
