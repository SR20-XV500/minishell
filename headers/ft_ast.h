/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ast.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:21:58 by tlassere          #+#    #+#             */
/*   Updated: 2024/01/27 18:05:03 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_AST_H
# define FT_AST_H

# define AST_ADD_LEFT 0
# define AST_ADD_RIGHT 1

typedef enum e_token
{
	TO_MAIN,
	TO_PIPE,
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
