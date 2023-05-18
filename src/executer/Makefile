# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 13:26:16 by ysalmi            #+#    #+#              #
#    Updated: 2023/05/18 12:18:57 by ysalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
N :=\x1b[0m
G :=\x1b[32;01m
R :=\x1b[31;01m
B :=\x1b[43;01m
O :=\x1b[33;01m
# **************************************************************************** #

NAME := executer.a

CC := cc
CFLAGS := -Wall -Wextra -Werror
I := -I../../inc -I../parser \
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


EXECUTER_SRC := executer.c \
		execute_simple_command.c \
		execute_compound_command.c \
		execute_subshell_command_bonus.c \
		prep_redirs.c \
		executer.utils.c \
		expand_var.c \
		split_content.c \
		expand.c \
		split_utils.c\
		expand_and_join.c\
		convert_lst_to_array.c \
		expansion_utils.c \
		../../gnline/get_next_line.c \
		../../gnline/get_next_line_utils.c \
		get_cmd_path.c \
		expand_heredoc.c

EXECUTER_BONUS :=




#**************************************************************************************#

SRC := 	../../gnline/get_next_line.c \
		../../gnline/get_next_line_utils.c \
		test.c \
		expand_heredoc.c \
		../parser/remove_quotes.c \
		expand_var.c \
		split_content.c \
		split_expanded_and_join.c \
		expand.c \
		remove_quotes_and_expand.c\
		split_utils.c\
		wildcard.c\
		expansion_utils.c \
		convert_list_to_array.c 


ex:  libft corelib dslib
	@$(CC) $(CFLAGS) $I $(READLINE)  $(LIBFT)  $(DS_LIB) $(CORE_LIB) $(LEXER_LIB)  $(SRC_T) -o ex
	./ex

#***************************************************************************************#

test: libft $(EXECUTER_SRC)
	@$(CC) $I $(CFLAGS) $(READLINE) -o $@ $(EXECUTER_SRC) $(LIBFT)
	@./$@


OBJ := $(SRC:%.c=%.o)
OBJ := $(addprefix obj/, $(OBJ))
