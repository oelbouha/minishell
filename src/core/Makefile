# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 13:26:16 by ysalmi            #+#    #+#              #
#    Updated: 2023/05/11 16:49:46 by ysalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := core.a

CC := cc
CFLAGS := -Wall -Wextra -Werror 
I := -I../../inc \
		-I../../libft/inc \
		-I../datastructures

LIBFT_DIR := ../../libft
LIBFT := ../../libft/libft.a

DS_DIR := ../datastructures
DS_LIB := ../datastructures/datastructures.a

CORE_SRC := builtins.c \
		cd.c \
		echo.c \
		env.c \
		export.c \
		pwd.c \
		setup.c \
		unset.c \
		get_current_wd.c \
		get_env_var.c \
		set_env_var.c \
		get_last_status.c \
		set_last_status.c \
		utils.c \

CORE_OBJ := $(CORE_SRC:%.c=%.o)
CORE_OBJ := $(addprefix obj/, $(CORE_OBJ))

N :=\x1b[0m
G :=\x1b[32;01m
R :=\x1b[31;01m
B :=\x1b[43;01m
O :=\x1b[33;01m

all: $(NAME)

$(NAME): $(CORE_OBJ)
	@ar -rcs $@ $^

test: libft dslib core_test

core_test: obj/test.o $(CORE_OBJ) $(LIBFT) $(DS_LIB)
	@$(CC) $(CFLAGS) $I $(READLINE) -o $@ $< $(CORE_OBJ) $(LIBFT) $(DS_LIB)

libft: 
	@make -s -C $(LIBFT_DIR)

dslib: 
	@make -s -C $(DS_DIR)

obj/%.o: %.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $I -c $< -o $@

clean:
	@rm -rf obj/

#@make -C $(LIBFT_DIR) clean
#@make -C $(DS_DIR) clean

fclean: clean
	@rm -rf $(NAME)

#@make -C $(LIBFT_DIR) fclean
#@make -C $(DS_DIR) fclean

re: fclean all

.PHONY: all lib clean fclean re test
