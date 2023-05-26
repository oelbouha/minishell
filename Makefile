# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 16:36:56 by ysalmi            #+#    #+#              #
#    Updated: 2023/05/26 16:50:31 by ysalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include src/core/Makefile src/lexer/Makefile src/parser/Makefile 
include src/executer/Makefile

NAME := minishell
BONUS := minishell_bonus

CFLAGS := -Wall -Wextra -Werror

I := -I../inc \
		-I/goinfre/$(USER)/brew/opt/readline/include \
		-Ilibft/inc \
		-Isrc/gnline \
		-Isrc/core \
		-Isrc/lexer \
		-Isrc/parser \
		-Isrc/executer \
		-Isrc/datastructures

READLINE := -lreadline \
		-I/goinfre/$(USER)/brew/opt/readline/include \
		-L/goinfre/$(USER)/brew/opt/readline/lib

LIBFT_DIR := libft

DS_DIR := src/datastructures

CORE_SRC := $(addprefix src/core/, $(CORE_SRC))

LEXER_SRC := $(addprefix src/lexer/, $(LEXER_SRC))
PARSER_SRC := $(addprefix src/parser/, $(PARSER_SRC))
EXECUTER_SRC := $(addprefix src/executer/, $(EXECUTER_SRC))

LEXER_BONUS := $(addprefix src/lexer/, $(LEXER_BONUS))
PARSER_BONUS := $(addprefix src/parser/, $(PARSER_BONUS))
EXECUTER_BONUS := $(addprefix src/executer/, $(EXECUTER_BONUS))

SRC := src/index.c \
	src/gnline/get_next_line.c \
	src/gnline/get_next_line_utils.c \
	$(CORE_SRC) \
	$(LEXER_SRC) \
	$(PARSER_SRC) \
	$(EXECUTER_SRC)

BSRC := src\index.c \
	src/gnline/get_next_line.c \
	src/gnline/get_next_line_utils.c \
	$(CORE_SRC) \
	$(LEXER_BONUS) \
	$(PARSER_BONUS) \
	$(EXECUTER_BONUS)

OBJ := $(SRC:%.c=%.o)
OBJ := $(addprefix obj/, $(OBJ))

BOBJ := $(BSRC:%.c=%.o)
BOBJ := $(addprefix obj/, $(BOBJ))

all: libft dslib $(NAME)

bonus: libft dslib $(BONUS)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a $(DS_DIR)/datastructures.a
	@$(CC) $(CFLAGS) $I $(READLINE) -o $@ $^

$(BONUS): $(BOBJ) $(LIBFT_DIR)/libft.a $(DS_DIR)/datastructures.a
	@$(CC) $(CFLAGS) $(READLINE) $I -o $@ $^

obj/%.o: %.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $I -c $< -o $@

libft: 
	@make -s -C $(LIBFT_DIR)

dslib: 
	@make -s -C $(DS_DIR)

clean:
	@rm -rf obj

fclean:
	@rm -rf obj $(NAME) $(BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(DS_DIR) fclean
