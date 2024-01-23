SOURCES = ft_atoi.c \
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
		  ft_dump_tab.c \
		  ft_free_tabs.c

BONUS_SRC  = ft_lstnew \
			 ft_lstadd_front \
			 ft_lstsize \
			 ft_lstlast \
			 ft_lstadd_back \
			 ft_lstdelone \
			 ft_lstclear \
			 ft_lstiter \
			 ft_lstmap

BONUS_FILE = $(foreach buffer, $(BONUS_SRC), $(buffer)_bonus.c)

OBJS = $(SOURCES:.c=.o)
OBJS_BONUS = $(BONUS_FILE:.c=.o)

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

CC = gcc

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_BONUS) libft.h
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
