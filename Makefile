# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 11:49:47 by ysalmi            #+#    #+#              #
#    Updated: 2023/03/24 18:02:28 by ysalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CFLAGS := -Wall -Wextra -Werror -g
I := -Iinc/ -Isrc/datastructures/ -Itests/
LIBFT_DIR := libft/
LIBFT := libft/libft.a



test: dict

lib:
	@make -s -C $(LIBFT_DIR)


DICT := tests/datastructures/dictionary.c \
	src/datastructures/dictionary.c

dict: lib $(DICT)
	@cc $(CFLAGS) $I -o $@ $(DICT) $(LIBFT)
	@./$@

	





.PHONY: lib rule one
