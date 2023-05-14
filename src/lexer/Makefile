# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 13:26:16 by ysalmi            #+#    #+#              #
#    Updated: 2023/05/11 21:46:53 by ysalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
N :=\x1b[0m
G :=\x1b[32;01m
R :=\x1b[31;01m
B :=\x1b[43;01m
O :=\x1b[33;01m
# **************************************************************************** #

NAME := lexer.a

CC := cc
CFLAGS := -Wall -Wextra -Werror
I := -I../../inc \
		-I../../libft/inc \
		-I../core
READLINE := -lreadline \
		-I/goinfre/$(USER)/brew/opt/readline/include \
		-L/goinfre/$(USER)/brew/opt/readline/lib

LIBFT_DIR := ../../libft
LIBFT := ../../libft/libft.a

DS_DIR := ../datastructures
DS_LIB := ../datastructures/datastructures.a

CORE_DIR := ../core
CORE_LIB := ../core/core.a

LSRC :=	get_line.c \
		tokenizer.c \
		split_line.c \
		handle_quotes.c \
		handle_token.c \
		handle_redir_and_pipe.c \
		utils.c	\
		simple_word.c \
		analyzer.c \
		analyzer.new.c \
		push_token_to_list.c

LOBJ := $(LSRC:%.c=%.o)
LOBJ := $(addprefix obj/, $(LOBJ))



BASE := read_line.c \
	tokenizer.c \
	analyzer.utils.c \
	utils.c

LEXER_SRC := $(BASE) \
	tokenizer.utils.c \
	analyzer.c \
	analyzer.check_common.c \
	lexer.utils.c

LEXER_BONUS := $(BASE) \
	tokenizer.utils_bonus.c \
	analyzer_bonus.c \
	analyzer.check_common_bonus.c \
	analyzer.check_logical_operators_bonus.c \
	analyzer.check_parentheses_bonus.c \
	lexer.utils_bonus.c

LEXER_SRC_OBJ := $(LEXER_SRC:%.c=%.o)
LEXER_SRC_OBJ := $(addprefix obj/, $(LEXER_SRC_OBJ))

LEXER_BONUS_OBJ := $(LEXER_BONUS:%.c=%.o)
LEXER_BONUS_OBJ := $(addprefix obj/, $(LEXER_BONUS_OBJ))

lbtest: main.c libft dslib corelib $(LEXER_BONUS_OBJ)
	@$(CC) $(CFLAGS) $I $(READLINE) -o $@ $< $(LEXER_BONUS_OBJ) \
		$(LIBFT) $(DS_LIB) $(CORE_LIB)
	./$@

lmtest: main.c libft dslib corelib $(LEXER_SRC_OBJ)
	@$(CC) $(CFLAGS) $I $(READLINE) -o $@ $< $(LEXER_SRC_OBJ) \
		$(LIBFT) $(DS_LIB) $(CORE_LIB)
	./$@
