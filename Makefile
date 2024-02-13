# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 02:19:35 by tlassere          #+#    #+#              #
#    Updated: 2024/02/08 21:22:41 by tlassere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES 		::= sources/
T_UTILS			::= ft_check_args_main ft_get_line ft_signal ft_pwd_usage ft_path_parser_join \
					ft_path_parser
UTILS			::= $(foreach buffer, $(T_UTILS), $(SOURCES)utils/$(buffer).c)
T_FT_PARSING	::= ft_data ft_word ft_parser ft_parser_get_elements ft_check_lst ft_type_set
FT_PARSING		::= $(foreach buffer, $(T_FT_PARSING), $(SOURCES)ft_parsing/$(buffer).c)
T_FT_BUILTIN	::= ft_env ft_env_get ft_env_iter ft_env_initial ft_env_initial_shlvl ft_echo ft_pwd ft_cd 
FT_BUILTIN		::= $(foreach buffer, $(T_FT_BUILTIN), $(SOURCES)ft_builtin/$(buffer).c)
SOURCES			::= $(SOURCES)main.c $(UTILS) $(FT_PARSING) $(FT_BUILTIN)
OBJS			::= $(SOURCES:.c=.o)
HEADERS			::= headers
HEADERS_CONTENT	::= headers/minishell.h headers/utils.h headers/ft_parsing.h headers/ft_env.h headers/ft_builtin.h
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
