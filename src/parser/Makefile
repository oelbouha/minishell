# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 13:26:16 by ysalmi            #+#    #+#              #
#    Updated: 2023/04/29 12:15:29 by ysalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
N :=\x1b[0m
G :=\x1b[32;01m
R :=\x1b[31;01m
B :=\x1b[43;01m
O :=\x1b[33;01m
# **************************************************************************** #

NAME := parser.a

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

SRC := new_command.c \
		new_simple_command.c \
		new_compound_command.c \
		new_redirection.c \
		new_file_redirection.c \
		new_heredoc_redirection.c \
		read_heredoc.c \
		expand.c \
		utils.c

#**************************************************************************************#

SRC_T := ../../gnline/get_next_line.c \
		../../gnline/get_next_line_utils.c \
		tests/main.c \
		expand_heredoc.c \
		expand_var.c 

ex:  libft dslib corelib lexerlib
	@$(CC) $(CFLAGS) $I $(READLINE)  $(LIBFT) $(CORE_LIB) $(DS_LIB) $(LEXER_LIB) $(SRC_T) -o ex

#***************************************************************************************#


OBJ := $(SRC:%.c=%.o)
OBJ := $(addprefix obj/, $(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $@ $(OBJ)

test: $(testfile) libft dslib corelib lexerlib $(NAME)
	@$(CC) $(CFLAGS) $I $(READLINE) -o $@ $< debug_utils.c $(OBJ) $(LIBFT) $(DS_LIB) $(CORE_LIB) $(LEXER_LIB)


libft: 
	@make -s -C $(LIBFT_DIR)

dslib: 
	@make -s -C $(DS_DIR)

corelib:
	@make -s -C $(CORE_DIR)

lexerlib:
	@make -s -C $(LEXER_DIR)

obj/%.o: %.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $I -c $< -o $@

clean:
	@rm -rf obj/
	@make -C $(LIBFT_DIR) clean
	@make -C $(CORE_DIR) clean
	@make -C $(LEXER_DIR) clean
	@make -C $(DS_DIR) clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf test
	@make -C $(LIBFT_DIR) fclean
	@make -C $(CORE_DIR) fclean
	@make -C $(LEXER_DIR) fclean
	@make -C $(DS_DIR) fclean

re: fclean all

.PHONY: all lib clean fclean re
