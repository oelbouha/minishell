# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 16:36:56 by ysalmi            #+#    #+#              #
#    Updated: 2023/05/23 21:00:55 by ysalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include core/Makefile lexer/Makefile parser/Makefile executer/Makefile

NAME := minishell
BONUS := minishell_bonus

CFLAGS := -Wall -Wextra -Werror #-g -fsanitize=address

I := -I../inc \
		-I/goinfre/$(USER)/brew/opt/readline/include \
		-I../libft/inc \
		-Icore \
		-Ilexer \
		-Iparser \
		-Iexecuter \
		-Idatastructures

READLINE := -lreadline \
		-I/goinfre/$(USER)/brew/opt/readline/include \
		-L/goinfre/$(USER)/brew/opt/readline/lib


LIBFT_DIR := ../libft

DS_DIR := datastructures
DS_LIB := datastructures/datastructures.a

CORE_SRC := $(addprefix core/, $(CORE_SRC))

LEXER_SRC := $(addprefix lexer/, $(LEXER_SRC))
PARSER_SRC := $(addprefix parser/, $(PARSER_SRC))
EXECUTER_SRC := $(addprefix executer/, $(EXECUTER_SRC))

LEXER_BONUS := $(addprefix lexer/, $(LEXER_BONUS))
PARSER_BONUS := $(addprefix parser/, $(PARSER_BONUS))
EXECUTER_BONUS := $(addprefix executer/, $(EXECUTER_BONUS))

SRC := index.c $(CORE_SRC) $(LEXER_SRC) $(PARSER_SRC) $(EXECUTER_SRC)
BSRC := index.c $(CORE_SRC) $(LEXER_BONUS) $(PARSER_BONUS) $(EXECUTER_BONUS)

OBJ := $(SRC:%.c=%.o)
OBJ := $(addprefix obj/, $(OBJ))

BOBJ := $(BSRC:%.c=%.o)
BOBJ := $(addprefix obj/, $(BOBJ))

all: libft dslib $(NAME)

bonus: libft dslib $(BONUS)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a $(DS_DIR)/datastructures.a
	@$(CC) $(CFLAGS) $I $(READLINE) -o minishell $^

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
