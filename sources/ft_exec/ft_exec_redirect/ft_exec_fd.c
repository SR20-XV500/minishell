/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 02:20:14 by tlassere          #+#    #+#             */
/*   Updated: 2024/03/04 15:48:52 by bcheronn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec_redirect_fd_err(t_data *data, int fd, const char *err_str,
		const char *path)
{
	int		status;
	char	*expansion;

	status = SUCCESS;
	expansion = NULL;
	if (fd == FD_FAIL_OPEN)
	{
		expansion = ft_trim_ambiguous(ft_expansion_get_str(data, err_str));
		status = FAIL;
		ft_fprintf(STDERR, "minishell: ");
		perror(expansion);
		data->env->exit_status = REDIRECT_FAIL;
	}
	else if (ft_is_directory(path) == SUCCESS)
	{
		expansion = ft_trim_ambiguous(ft_expansion_get_str(data, err_str));
		status = FAIL;
		ft_fprintf(STDERR, "minishell: %s: Is a directory\n", expansion);
		data->env->exit_status = REDIRECT_FAIL;
	}
	if (expansion)
		free(expansion);
	return (status);
}

/**
 * In open for stdout redirection, flags 0644 is specified.
 * Its meaning is :
 * * 0: permissions are set in octal
 * * 6: to allow the user's read and write access
 * * 4: to allow read mode for the group
 * * 4: to allow read mode for others
 */
int	ft_exec_redirect_fd(t_data *data, int type, const char *path,
		const char *err_str)
{
	int	status;
	int	open_fd;
	int	*change_fd;

	status = BAD_PARAMETER;
	if (data && path && err_str)
	{
		change_fd = &(data->output_fd);
		if (type == D_INPUT)
			change_fd = &(data->input_fd);
		if (type == D_INPUT)
			open_fd = open(path, O_RDONLY);
		else if (type == D_OUTPUT_NEW)
			open_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, OPEN_WR_R_R);
		else
			open_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, OPEN_WR_R_R);
		if (open_fd)
		{
			if (*change_fd > MAX_OPEN_PRE_OPEN)
				close(*change_fd);
			*change_fd = open_fd;
		}
		status = ft_exec_redirect_fd_err(data, open_fd, err_str, path);
	}
	return (status);
}

static int	ft_exec_redirect_content(t_data *data, int type, t_word *word_path)
{
	int		status;
	char	*path;

	status = BAD_PARAMETER;
	path = NULL;
	if (data && type && word_path && word_path->word)
	{
		status = FAIL;
		path = ft_redirect_get_path(data, word_path->word);
		if (path)
		{
			status = ft_exec_redirect_fd(data, type, path, word_path->word);
			free(path);
		}
	}
	return (status);
}

int	ft_exec_redirect(t_data *data, t_list *lst)
{
	int	status;
	int	type;

	status = BAD_PARAMETER;
	if (data && lst && lst->content)
	{
		status = SUCCESS;
		type = ((t_word *)lst->content)->type;
		if (type == D_INPUT || type == D_OUTPUT_APPEND || type == D_OUTPUT_NEW)
		{
			if (lst->next && lst->next->content
				&& ((t_word *)lst->next->content)->type == TY_PATH)
			{
				status = ft_exec_redirect_content(data, type,
						lst->next->content);
			}
			else
				status = FAIL;
		}
		else if (type == D_PIPE)
			status = D_PIPE;
	}
	return (status);
}
