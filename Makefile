# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 19:16:00 by oelbouha          #+#    #+#              #
#    Updated: 2023/03/10 19:16:03 by oelbouha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := cc

CFLAGS := -Wall -Wextra -Werror

RM := rm -f

SRC := 	libft/ft_split.c \
		libft/ft_strchr.c \
		libft/ft_substr.c \
		libft/ft_strlen.c \
		libft/ft_strtrim.c \
		libft/ft_putstr_fd.c \
		libft/ft_strncmp.c \
		libft/ft_strjoin.c \
		libft/split.c \
		parser/parser.c \
		run_command.c \
		execute_commands.c \
		print_error_msg.c \
		libft/ft_search.c \
		main.c


OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

clean: 
	@${RM} $(OBJ)

fclean: clean
	@${RM} $(NAME)

re: fclean all

.PHONY: all clean fclean re
