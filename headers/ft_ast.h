/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:21:58 by tlassere          #+#    #+#             */
/*   Updated: 2024/01/27 17:53:28 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_AST_H
# define FT_AST_H

typedef enum e_token
{
	TO_PIPE = 0,
	TO_CMD	
}	t_token;

typedef struct s_ast
{
	t_token			type;
	char			*content;	
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

#endif
