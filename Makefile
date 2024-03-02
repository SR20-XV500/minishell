# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcheronn <bcheronn@student.42mulhouse>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 02:19:35 by tlassere          #+#    #+#              #
#    Updated: 2024/03/02 23:49:27 by tlassere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			::= minishell
SOURCES 		::= sources/
T_UTILS			::= ft_check_args_main ft_get_line ft_signal ft_pwd_usage \
					ft_path_parser_join ft_path_parser ft_file_checks \
					ft_quicksort ft_path_multi
UTILS			::= $(foreach buffer, $(T_UTILS), $(SOURCES)utils/$(buffer).c)
T_FT_EXEC_PIPE	::= ft_exec_cmd_children ft_exec_cmd_children_2 ft_exec_pipe
FT_EXEC_PIPE	::= $(foreach buffer, $(T_FT_EXEC_PIPE), \
						ft_exec_pipe/$(buffer))
T_FT_EXEC_RED	::= ft_redirect_path ft_exec_fd ft_exec_dup \
					ft_exec_here_doc ft_exec_here_doc_delimitor \
					ft_exec_here_doc_redirect
FT_EXEC_RED		::= $(foreach buffer, $(T_FT_EXEC_RED), \
						ft_exec_redirect/$(buffer))
T_FT_EXEC		::= ft_exec ft_exec_cmd_path $(FT_EXEC_RED) $(FT_EXEC_PIPE) \
					ft_exec_cmd ft_exec_cmd_free ft_exec_cmd_true
FT_EXEC			::= $(foreach buffer, $(T_FT_EXEC),\
						$(SOURCES)ft_exec/$(buffer).c)
T_FT_PARSING_EX	::= ft_expansion_get ft_expansion_var_join ft_expansion_split \
					ft_expansion_split_main ft_expansion \
					ft_expantion_get_str_func 
FT_PARSING_EX	::= $(foreach buffer, $(T_FT_PARSING_EX), \
						ft_expansion/$(buffer))
T_FT_PARSING	::= ft_parser ft_parser_get_elements ft_check_lst ft_type_set \
					ft_rm_rf_quotes $(FT_PARSING_EX)
FT_PARSING		::= $(foreach buffer, $(T_FT_PARSING), \
						$(SOURCES)ft_parsing/$(buffer).c)
T_FT_BUILTINS	::= ft_echo ft_pwd ft_cd ft_unset ft_export ft_export_print \
					ft_exit ft_env
FT_BUILTINS		::= $(foreach buffer, $(T_FT_BUILTINS), \
						$(SOURCES)ft_builtins/$(buffer).c)
T_FT_ENV		::= ft_env_data ft_env_tab_get ft_env_get ft_env_iter \
					ft_env_initial ft_env_initial_shlvl
FT_ENV			::= $(foreach buffer, $(T_FT_ENV), \
						$(SOURCES)ft_env/$(buffer).c)
T_FT_DATA		::= ft_data ft_word ft_word_lst
FT_DATA			::= $(foreach buffer, $(T_FT_DATA), \
						$(SOURCES)ft_data/$(buffer).c)
SOURCES			::= $(SOURCES)main.c $(UTILS) $(FT_PARSING) $(FT_BUILTINS) \
					$(FT_EXEC) $(FT_ENV) $(FT_DATA)
OBJS			::= $(SOURCES:.c=.o)
HEADERS			::= headers/
HEADERS_CONTENT	::= $(HEADERS)minishell.h $(HEADERS)utils.h \
					$(HEADERS)ft_parsing.h $(HEADERS)ft_env.h \
					$(HEADERS)ft_builtins.h $(HEADERS)ft_exec.h \
					$(HEADERS)ft_data.h 
LIBFT_DIR		::= libft/
LIBFT			::= $(LIBFT_DIR)libft.a
CFLAGS			::= -Wall -Wextra -Werror
LDFLAGS			::= $(CFLAGS) -lreadline

all: $(NAME)

.c.o :
	$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIBFT_DIR) -c -o $@ $<

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
