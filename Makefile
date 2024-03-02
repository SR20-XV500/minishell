# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 02:19:35 by tlassere          #+#    #+#              #
#    Updated: 2024/02/17 22:44:07 by bcheronn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			::= minishell
SOURCES 		::= sources/
T_UTILS			::= ft_check_args_main ft_get_line ft_signal ft_pwd_usage \
					ft_path_parser_join ft_path_parser ft_file_checks \
					ft_path_multie ft_quicksort
UTILS			::= $(foreach buffer, $(T_UTILS), $(SOURCES)utils/$(buffer).c)
T_FT_EXEC		::= ft_redirect_path ft_exec ft_exec_fd ft_exec_cmd_path \
					ft_exec_cmd ft_exec_cmd_free ft_exec_cmd_true ft_exec_dup \
					ft_exec_cmd_children ft_exec_cmd_children_2 ft_exec_pipe \
					ft_exec_here_doc ft_exec_here_doc_delimitor \
					ft_exec_here_doc_redirect
FT_EXEC			::= $(foreach buffer, $(T_FT_EXEC),\
						$(SOURCES)ft_exec/$(buffer).c)
T_FT_PARSING	::= ft_data ft_word ft_parser ft_parser_get_elements \
					ft_check_lst ft_type_set ft_expansion \
					ft_expansion_get ft_expansion_var_join ft_expansion_split \
					ft_expansion_split_main ft_rm_rf_quotes ft_word_lst \
					ft_expention_get_str_func
FT_PARSING		::= $(foreach buffer, $(T_FT_PARSING), \
						$(SOURCES)ft_parsing/$(buffer).c)
T_FT_BUILTINS	::= ft_env ft_env_tab_get ft_env_get ft_env_iter \
					ft_env_initial ft_env_initial_shlvl ft_echo ft_pwd ft_cd \
					ft_unset ft_export ft_export_print ft_exit
FT_BUILTINS		::= $(foreach buffer, $(T_FT_BUILTINS), \
						$(SOURCES)ft_builtins/$(buffer).c)
SOURCES			::= $(SOURCES)main.c $(UTILS) $(FT_PARSING) $(FT_BUILTINS) \
					$(FT_EXEC)
OBJS			::= $(SOURCES:.c=.o)
HEADERS			::= headers/
HEADERS_CONTENT	::= $(HEADERS)minishell.h $(HEADERS)utils.h \
					$(HEADERS)ft_parsing.h $(HEADERS)ft_env.h \
					$(HEADERS)ft_builtins.h $(HEADERS)ft_exec.h
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
