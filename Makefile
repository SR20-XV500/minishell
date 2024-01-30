# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 02:19:35 by tlassere          #+#    #+#              #
#    Updated: 2024/01/25 01:12:34 by bcheronn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES 		::= sources/
T_UTILS			::= ft_check_args_main \
					ft_get_line
UTILS			::= $(foreach buffer, $(T_UTILS), $(SOURCES)utils/$(buffer).c)
T_FT_AST		::= ft_ast
FT_AST			::= $(foreach buffer, $(T_FT_AST), $(SOURCES)ft_ast/$(buffer).c)
T_FT_BUILTIN	::= ft_env
FT_BUILTIN		::= $(foreach buffer, $(T_FT_BUILTIN), $(SOURCES)ft_builtin/$(buffer).c)
SOURCES			::= $(SOURCES)main.c $(UTILS) $(FT_AST) $(FT_BUILTIN)
OBJS			::= $(SOURCES:.c=.o)
HEADERS			::= headers
HEADERS_CONTENT	::= headers/minishell.h headers/utils.h headers/ft_ast.h headers/ft_env.h
NAME			::= minishell
LIBFT			::= libft/libft.a
CFLAGS			::= -Wall -Wextra -Werror
LDFLAGS			::= $(CFLAGS) -lreadline
all: $(NAME)

.c.o :
	$(CC) $(CFLAGS) -I $(HEADERS) -c -o $@ $<

$(NAME): $(LIBFT) $(OBJS) $(HEADERS_CONTENT)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

clean:
	rm -rf $(OBJS)
	make -C libft clean

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
