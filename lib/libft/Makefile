# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chheniqu <chheniqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 13:19:27 by armarboe          #+#    #+#              #
#    Updated: 2025/06/04 12:24:26 by chheniqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

HEADERS_DIR=./includes
SRCS_DIR=./srcs

CHAR_HANDLING_DIR=${SRCS_DIR}/char_handling/
CONVERSIONS_DIR=${SRCS_DIR}/conversions/
FILE_IO_DIR=${SRCS_DIR}/file_io/
FT_PRINTF_DIR=${SRCS_DIR}/ft_printf/
GET_NEXT_LINE_DIR=${SRCS_DIR}/get_next_line/
LINKED_LISTS_DIR=${SRCS_DIR}/linked_lists/
MEMORY_UTILS_DIR=${SRCS_DIR}/memory_utils/
STRING_UTILS_DIR=${SRCS_DIR}/string_utils/

CHAR_HANDLING_SRCS= \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_tolower.c \
	ft_toupper.c

CONVERSIONS_SRCS= \
	ft_atoi.c \
	ft_atoi_base.c \
	ft_itoa.c

FILE_IO_SRCS= \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c

FT_PRINTF_SRCS= \
	ft_printf_char.c \
	ft_printf_hexadecimal.c \
	ft_printf_nbr.c \
	ft_printf_percent.c \
	ft_printf_pointer.c \
	ft_printf_str.c \
	ft_printf_unsigned_nbr.c \
	ft_printf.c \

GET_NEXT_LINE_SRCS= \
	get_next_line.c \
	get_next_line_utils.c

LINKED_LISTS_SRCS= \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstadd_back.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c

MEMORY_UTILS_SRCS= \
	free_tab_char.c \
	free_tab_int.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_memset.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c

STRING_UTILS_SRCS= \
	ft_strlen.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strcmp.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strdup.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_split.c

SRCS=$(addprefix $(CHAR_HANDLING_DIR), $(CHAR_HANDLING_SRCS)) \
		$(addprefix $(CONVERSIONS_DIR), $(CONVERSIONS_SRCS)) \
		$(addprefix $(FILE_IO_DIR), $(FILE_IO_SRCS)) \
		$(addprefix $(FT_PRINTF_DIR), $(FT_PRINTF_SRCS)) \
		$(addprefix $(GET_NEXT_LINE_DIR), $(GET_NEXT_LINE_SRCS)) \
		$(addprefix $(LINKED_LISTS_DIR), $(LINKED_LISTS_SRCS)) \
		$(addprefix $(MEMORY_UTILS_DIR), $(MEMORY_UTILS_SRCS)) \
		$(addprefix $(STRING_UTILS_DIR), $(STRING_UTILS_SRCS)) \

OBJS=${SRCS:.c=.o}

CC=cc
CFLAGS=-Wall -Wextra -Werror -I ${HEADERS_DIR} -g3

COLOR_ORANGE=\033[38;5;214m
RESET_COLOR=\033[0m

all: ${NAME}

${NAME}: ${OBJS}
		@echo "$(COLOR_ORANGE)Compiling $(NAME)...$(RESET_COLOR)"
		ar rcs ${NAME} ${OBJS}
		@echo "$(COLOR_ORANGE)Libft.a has been successfully compiled.$(RESET_COLOR)"

clean: 
		rm -f ${OBJS}

fclean: clean
		rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
