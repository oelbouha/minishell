# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 13:26:16 by ysalmi            #+#    #+#              #
#    Updated: 2023/05/11 16:39:45 by ysalmi           ###   ########.fr        #
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

SRC :=	get_line.c \
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

OBJ := $(SRC:%.c=%.o)
OBJ := $(addprefix obj/, $(OBJ))



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

lexer_bonus: main.c libft dslib corelib $(LEXER_BONUS_OBJ)
	@$(CC) $(CFLAGS) $I $(READLINE) -o $@ $< $(LEXER_BONUS_OBJ) \
		$(LIBFT) $(DS_LIB) $(CORE_LIB)
	./lexer_bonus

lexer_mandatory: main.c libft dslib corelib $(LEXER_SRC_OBJ)
	@$(CC) $(CFLAGS) $I $(READLINE) -o $@ $< $(LEXER_SRC_OBJ) \
		$(LIBFT) $(DS_LIB) $(CORE_LIB)
	./lexer_mandatory

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $@ $(OBJ)

libft: 
	@make -s -C $(LIBFT_DIR)

dslib: 
	@make -s -C $(DS_DIR)

corelib:
	@make -s -C $(CORE_DIR)

obj/%.o: %.c lexer.h
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $I -c $< -o $@

clean:
	@rm -rf obj/
	@make -C $(LIBFT_DIR) clean
	@make -C $(CORE_DIR) clean
	@make -C $(DS_DIR) clean

fclean: clean
	@rm -rf $(NAME) lexer test
	@rm -rf test
	@make -C $(LIBFT_DIR) fclean
	@make -C $(CORE_DIR) fclean
	@make -C $(DS_DIR) fclean

re: fclean all

.PHONY: all lib clean fclean re
