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

UTILS	::= sources/utils/ft_check_args_main.c

SOURCES	::= sources/main.c \
			$(UTILS)
OBJS	::= $(SOURCES:.c=.o)
HEADERS	::= headers
NAME	::= minishell
LIBFT	::= libft/libft.a
CFLAGS	::= -Wall -Wextra -Werror
all: $(NAME)

.c.o :
	$(CC) $(CFLAGS) -I $(HEADERS) -c -o $@ $<

$(NAME): $(LIBFT) $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

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
