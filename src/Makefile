# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 16:36:56 by ysalmi            #+#    #+#              #
#    Updated: 2023/05/23 20:23:11 by ysalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include core/Makefile lexer/Makefile parser/Makefile executer/Makefile

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
BONUS := index.c $(CORE_SRC) $(LEXER_BONUS) $(PARSER_BONUS) $(EXECUTER_BONUS)


OBJ := $(SRC:%.c=%.o)
OBJ := $(addprefix obj/, $(OBJ))

BOBJ := $(BONUS:%.c=%.o)
BOBJ := $(addprefix obj/, $(BOBJ))


mtest: $(OBJ) libft dslib
	@$(CC) $(CFLAGS) $I $(READLINE) -o minishell $(OBJ) $(LIBFT_DIR)/libft.a $(DS_LIB)
	
btest: $(BOBJ) libft dslib
	@$(CC) $(CFLAGS) $(READLINE) $I -o $@ $(BOBJ) $(LIBFT_DIR)/libft.a $(DS_LIB)

echo:
	@echo $(READLINE)

echo_bonus:
	@echo $(BONUS)

obj/%.o: %.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $I -c $< -o $@

libft: 
	@make -s -C $(LIBFT_DIR)

dslib: 
	@make -s -C $(DS_DIR)

fclean:
	@rm -rf obj mtest btest
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(DS_DIR) fclean
