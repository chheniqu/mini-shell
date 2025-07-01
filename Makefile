# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 23:10:48 by armarboe          #+#    #+#              #
#    Updated: 2025/07/01 18:09:21 by chheniqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADERS_DIR = ./includes
SRCS_DIR = ./srcs

BUILTINS_DIR = ${SRCS_DIR}/builtins/
CLEAN_DIR = ${SRCS_DIR}/clean/
MINISHELL_DIR = ${SRCS_DIR}/minishell/
PARSER_DIR = ${SRCS_DIR}/parser/
PIPEX_DIR = ${SRCS_DIR}/pipex/
READLINE_DIR = ${SRCS_DIR}/readline/
SIGNALS_DIR = ${SRCS_DIR}/signals/
SYNTAX_DIR = ${SRCS_DIR}/syntax/
TOKENIZATION_DIR = ${SRCS_DIR}/tokenization/
EXPAND_DIR = ${SRCS_DIR}/expand/

BUILTINS_SRCS = \
	builtins_utils.c \
	env_handler.c \
	export_utils.c \
	ft_cd.c \
	ft_echo.c \
	ft_env.c \
	ft_exit.c \
	ft_export.c \
	ft_pwd.c \
	ft_unset.c \

CLEAN_SRCS = \
	clean.c \
	
MINISHELL_SRCS = \
	minishell.c \

PARSER_SRCS = \
	parser_utils.c \
	parser.c \
	redir_list.c \
	shell_cmd_list.c \

PIPEX_SRCS = \
	check_pipex1.c \
	check_pipex2.c \
	clean_pipex.c \
	close_fd.c \
	create_cmd_list.c \
	get_command.c \
	get_env_pipex.c \
	handle_builtins_utils.c \
	handle_builtins.c \
	handle_heredoc.c \
	handle_redirections.c \
	handle_redirections_utils.c \
	pid.c \
	pipex_utils.c \
	pipex.c \
	split_minishell_utils.c \
	split_minishell.c \

READLINE_SRCS = \
	readline.c \

SIGNALS_SRCS = \
	handle_signals.c \
	init_signals.c \

SYNTAX_SRCS = \
	syntax.c \

TOKENIZATION_SRCS = \
	add_token.c \
	tokenization.c \
	tokens_error.c \
	tokens_type.c \
	extract_word.c \
	remove_quotes.c \
	process_token.c \

EXPAND_SRCS = \
	expand.c \
	expand_utils.c \
	expand_utils_2.c \

SRCS = 	${addprefix ${BUILTINS_DIR}, ${BUILTINS_SRCS}} \
		${addprefix ${CLEAN_DIR}, ${CLEAN_SRCS}} \
		${addprefix ${MINISHELL_DIR}, ${MINISHELL_SRCS}} \
		${addprefix ${PARSER_DIR}, ${PARSER_SRCS}} \
		${addprefix ${PIPEX_DIR}, ${PIPEX_SRCS}} \
		${addprefix ${READLINE_DIR}, ${READLINE_SRCS}} \
		${addprefix ${SYNTAX_DIR}, ${SYNTAX_SRCS}} \
		${addprefix ${TOKENIZATION_DIR}, ${TOKENIZATION_SRCS}} \
		${addprefix ${EXPAND_DIR}, ${EXPAND_SRCS}} \
		${addprefix ${SIGNALS_DIR}, ${SIGNALS_SRCS}} \

OBJS = ${SRCS:.c=.o}
LIBFT_DIR = lib/libft
LIBFT = ${LIBFT_DIR}/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ${HEADERS_DIR} -I ${LIBFT_DIR} -g3
LFLAGS = -L ${LIBFT_DIR} -lft -lreadline -lncurses

COLOR_GREEN = \033[38;5;84m
COLOR_PURPLE = \033[95m
RESET_COLOR = \033[0m

all: ${LIBFT} ${NAME}

valgrind: all
	@valgrind --trace-children=yes --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=supp.supp ./$(NAME)

${NAME}: ${OBJS}
	@echo "${COLOR_PURPLE}Compiling ${NAME}...${RESET_COLOR}"
	${CC} ${CFLAGS} ${OBJS} ${LFLAGS} -o ${NAME}
	@echo "${COLOR_PURPLE}${NAME} has been successfully compiled.${RESET_COLOR}"

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${LIBFT}:
	@make -sC ${LIBFT_DIR}

clean: 
	@echo "$(COLOR_GREEN)Deleting object files...$(RESET_COLOR)"
	@rm -f ${OBJS} ${BONUS_OBJS}
	@make -sC ${LIBFT_DIR} clean
	@echo "$(COLOR_GREEN)Object files have been cleaned up successfully.$(RESET_COLOR)"

fclean: clean
	@echo "$(COLOR_GREEN)Deleting executables...$(RESET_COLOR)"
	@rm -f ${NAME} ${BONUS_NAME}
	@make -sC ${LIBFT_DIR} fclean
	@echo "${COLOR_GREEN}All executables and objects have been cleaned up successfully.${RESET_COLOR}"

re: fclean all

.PHONY: all clean fclean re
