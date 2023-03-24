# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 13:26:16 by ysalmi            #+#    #+#              #
#    Updated: 2023/03/23 14:04:25 by ysalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := lexer
CC := cc
CFLAGS := -Wall -Wextra -Werror
I := -I../../inc -I../../libft/inc
READLINE := -lreadline
LIBFT_DIR := ../../libft
LIBFT := ../../libft/libft.a

SRC := get_input.c

OBJ := $(SRC:%.c=%.o)
OBJ := $(addprefix obj/, $(OBJ))


N :=\x1b[0m
G :=\x1b[32;01m
R :=\x1b[31;01m
B :=\x1b[43;01m
O :=\x1b[33;01m

all: lib $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(READLINE) -o $@ $(OBJ) $(LIBFT)

lib: 
	@make -C $(LIBFT_DIR)

obj/%.o: %.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $I -c $< -o $@

clean:
	@rm -rf obj/

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all lib clean fclean re
