/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 02:16:41 by tlassere          #+#    #+#             */
/*   Updated: 2024/02/12 22:26:02 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: implement parser to readline

static void	ft_print_word(t_list *lst)
{
	if (lst)
	{
		ft_printf("%s\n", ((t_word *)lst->content)->word);
		ft_print_word(lst->next);
	}
}

int	main(int argc, char **argv, const char **envp)
{
	t_data	*data;

	//ft_check_args_main(argc);
	data = ft_data_get(envp);
	//if (data && ft_signal() == SIGNAL_HANDLING)
	//{
		if (ft_parser(data, argv[1]) != MALLOC_FAIL)
			ft_print_word(data->words);
		//ft_use_line();
		ft_data_free(&data);
	//}
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
