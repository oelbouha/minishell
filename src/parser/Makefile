# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 13:26:16 by ysalmi            #+#    #+#              #
#    Updated: 2023/04/12 23:36:01 by ysalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := lexer
CC := cc
CFLAGS := -Wall -Wextra -Werror
I := -I../../inc -I../../libft/inc -I../core -I.
READLINE := -lreadline -I/goinfre/ysalmi/brew/opt/readline/include \
	-L/goinfre/ysalmi/brew/opt/readline/lib
LIBFT_DIR := ../../libft
LIBFT := ../../libft/libft.a
DS_DIR := ../datastructures
DS_LIB := ../datastructures/datastructures.a
CORE_DIR := ../core
CORE_LIB := ../core/core.a

SRC :=	split_line.c \
		handle_quotes.c \
		handle_redir_and_pipe.c \
		main.c	\
		utils.c	\
		simple_word.c

OBJ := $(SRC:%.c=%.o)
OBJ := $(addprefix obj/, $(OBJ))

test: libft heredoc

heredoc: main.c new_heredoc_redirection.c expand.c
	@cc $(CFLAGS) $I $^ $(LIBFT) -o $@ 


N :=\x1b[0m
G :=\x1b[32;01m
R :=\x1b[31;01m
B :=\x1b[43;01m
O :=\x1b[33;01m

all: libft dslib corelib $(NAME)

$(NAME): $(OBJ) $(LIBFT) lexer.h
	@$(CC) $(CFLAGS) $(READLINE) -o $@ $(OBJ) $(LIBFT) $(DS_LIB) $(CORE_LIB)

libft: 
	@make -s -C $(LIBFT_DIR)

dslib: 
	@make -s -C $(DS_DIR)

corelib:
	@make -s -C $(CORE_DIR)

obj/%.o: %.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $I -c $< -o $@

clean:
	@rm -rf obj/
	@make -C $(LIBFT_DIR) clean
	@make -C $(CORE_DIR) clean
	@make -C $(DS_DIR) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf test
	@make -C $(LIBFT_DIR) fclean
	@make -C $(CORE_DIR) fclean
	@make -C $(DS_DIR) fclean

re: fclean all

.PHONY: all lib clean fclean re
