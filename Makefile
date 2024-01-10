SOURCES = 	sources/main.c

OBJS = $(SOURCES:.c=.o)

HEADERS = headers

NAME = minishell
LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror -g3 -I headers
CC = cc

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) $(LIBFT)
	$(CC) $(CFLAGS) -I $(HEADERS) $(OBJS) -o $(NAME)

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
