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
SOURCES			::= $(SOURCES)main.c \
					$(UTILS)
OBJS			::= $(SOURCES:.c=.o)
HEADERS			::= headers
HEADERS_CONTENT	::= headers/minishell.h \
					headers/utils.h \
					headers/ft_ast.h
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
