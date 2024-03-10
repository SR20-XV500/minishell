# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 02:19:24 by tlassere          #+#    #+#              #
#    Updated: 2024/01/24 02:19:24 by tlassere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES	::= ft_atoi.c \
			ft_atoll.c \
		  	ft_bzero.c \
		  	ft_isalnum.c \
		  	ft_isalpha.c \
		  	ft_isascii.c \
		  	ft_isdigit.c \
		  	ft_isprint.c \
		  	ft_memcmp.c \
		  	ft_memcpy.c \
		  	ft_memchr.c \
		  	ft_memmove.c \
		  	ft_memset.c \
		  	ft_strlcat.c \
		  	ft_strchr.c \
		  	ft_strdup.c\
		  	ft_strlen.c \
		  	ft_strncmp.c \
		  	ft_strcmp_s2.c \
		  	ft_strrchr.c \
		  	ft_strnstr.c \
		  	ft_calloc.c \
		  	ft_tolower.c \
		  	ft_substr.c \
		  	ft_putchar_fd.c \
		  	ft_putstr_fd.c \
		  	ft_putnbr_fd.c \
		  	ft_strjoin.c \
		  	ft_strtrim.c \
		  	ft_split.c \
		  	ft_itoa.c \
		  	ft_putendl_fd.c \
		  	ft_strlcpy.c \
		  	ft_strmapi.c \
		  	ft_striteri.c \
		  	ft_toupper.c \
		  	ft_abs.c \
		  	ft_strrev.c \
		  	ft_int_convert_base.c \
		  	ft_uint_convert_base.c \
		  	ft_bt8_convert_base.c \
		  	get_next_line.c \
		  	get_next_line_utils.c \
		  	ft_printf/sources/ft_printf.c \
		  	ft_printf/sources/ft_printf_utils.c \
		  	ft_printf/sources/ft_printf_utils2.c \
		  	ft_tab_dump.c \
		  	ft_tab_free.c\
			ft_tab_len.c \
		  	ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_tab_join.c \
			ft_tab_dump_join.c \
			ft_tab_del.c \
			ft_check_overflow.c
OBJS 	::= $(SOURCES:.c=.o)
NAME 	::= libft.a
CFLAGS	::= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) libft.h
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
