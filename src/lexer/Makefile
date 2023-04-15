# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 13:26:16 by ysalmi            #+#    #+#              #
#    Updated: 2023/04/13 23:27:04 by ysalmi           ###   ########.fr        #
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
		split_line.c \
		handle_quotes.c \
		handle_token.c \
		handle_redir_and_pipe.c \
		utils.c	\
		simple_word.c \
		analyzer.c \
		push_token_to_list.c

OBJ := $(SRC:%.c=%.o)
OBJ := $(addprefix obj/, $(OBJ))


lexer: main.c libft dslib corelib $(NAME)
	@$(CC) $(CFLAGS) $I $(READLINE) -o $@ $< $(NAME) $(LIBFT) $(DS_LIB) $(CORE_LIB)
	
test: $(testfile) libft dslib corelib $(NAME)
	$(CC) $(CFLAGS) $I $(READLINE) -o $@ $< $(NAME) $(LIBFT) $(DS_LIB) $(CORE_LIB)

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
