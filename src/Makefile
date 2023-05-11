# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 16:36:56 by ysalmi            #+#    #+#              #
#    Updated: 2023/05/11 17:36:51 by ysalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include core/Makefile lexer/Makefile

I := -I../inc \
		-I../libft/inc \
		-Icore \
		-Ilexer \
		-Iparser \
		-Idatastructures

READLINE := -lreadline \
		-I/goinfre/$(USER)/brew/opt/readline/include \
		-L/goinfre/$(USER)/brew/opt/readline/lib

LIBFT_DIR := ../../libft
LIBFT_DIR := ../libft
LIBFT := ../libft/libft.a

DS_DIR := datastructures
DS_LIB := datastructures/datastructures.a

CORE_SRC := $(addprefix core/, $(CORE_SRC))
LEXER_SRC := $(addprefix lexer/, $(LEXER_SRC))

LEXER_BONUS := $(addprefix lexer/, $(LEXER_BONUS))

SRC := index.c $(CORE_SRC) $(LEXER_SRC)
BONUS := index.c $(CORE_SRC) $(LEXER_BONUS)

OBJ := $(SRC:%.c=%.o)
OBJ := $(addprefix obj/, $(OBJ))

BOBJ := $(BONUS:%.c=%.o)
BOBJ := $(addprefix obj/, $(BOBJ))


mtest: $(OBJ) libft dslib
	@$(CC) $(CFLAGS) $I $(READLINE) -o $@ $(OBJ) $(LIBFT) $(DS_LIB)
	./$@
	
btest: $(BOBJ) libft dslib
	@$(CC) $(CFLAGS) $I $(READLINE) -o $@ $(BOBJ) $(LIBFT) $(DS_LIB)
	./$@

obj/%.o: %.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $I -c $< -o $@

libft: 
	@make -s -C $(LIBFT_DIR)

dslib: 
	@make -s -C $(DS_DIR)

