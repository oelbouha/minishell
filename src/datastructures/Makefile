# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 13:26:16 by ysalmi            #+#    #+#              #
#    Updated: 2023/04/07 16:32:14 by ysalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := datastructures.a
CC := cc
CFLAGS := -Wall -Wextra -Werror
I := -I../../inc -I../../libft/inc -I../datastructures
LIBFT_DIR := ../../libft
LIBFT := ../../libft/libft.a

SRC := dictionary_01.c \
		dictionary_02.c

OBJ := $(SRC:%.c=%.o)
OBJ := $(addprefix obj/, $(OBJ))




N :=\x1b[0m
G :=\x1b[32;01m
R :=\x1b[31;01m
B :=\x1b[43;01m
O :=\x1b[33;01m

all: $(NAME)

$(NAME): $(OBJ) 
	ar -rcs $(NAME) $(OBJ)

lib: 
	@make -s -C $(LIBFT_DIR)

obj/%.o: %.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $I -c $< -o $@

clean:
	@rm -rf obj/

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all lib clean fclean re
