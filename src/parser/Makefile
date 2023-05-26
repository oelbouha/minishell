# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 13:26:16 by ysalmi            #+#    #+#              #
#    Updated: 2023/05/26 17:15:45 by ysalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
N :=\x1b[0m
G :=\x1b[32;01m
R :=\x1b[31;01m
B :=\x1b[43;01m
O :=\x1b[33;01m
# **************************************************************************** #

CC := cc
CFLAGS := -Wall -Wextra -Werror
I := -I../../inc \
		-I../../libft/inc \
		-I../core \
		-I../lexer \
		-I./

READLINE := -lreadline \
		-I/goinfre/ysalmi/brew/opt/readline/include \
		-L/goinfre/ysalmi/brew/opt/readline/lib

LIBFT_DIR := ../../libft
LIBFT := ../../libft/libft.a

DS_DIR := ../datastructures
DS_LIB := ../datastructures/datastructures.a

CORE_DIR := ../core
CORE_LIB := ../core/core.a

LEXER_DIR := ../lexer
LEXER_LIB := ../lexer/lexer.a

BASE :=	new_simple_command.c \
		new_redirection.c \
		new_file_redirection.c \
		new_heredoc_redirection.c \
		read_heredoc.c \
		remove_quotes.c \
		parser.utils.c 

PARSER_SRC := $(BASE) \
		new_command.c \
		new_compound_command.c

PARSER_BONUS := $(BASE) \
		new_command_bonus.c \
		new_compound_command_bonus.c \
		new_subshell_command_bonus.c

PARSER_OBJ := $(PARSER_SRC:%.c=%.o)
PARSER_OBJ := $(addprefix obj/, $(PARSER_OBJ))
