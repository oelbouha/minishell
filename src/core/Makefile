# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysalmi <ysalmi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 13:26:16 by ysalmi            #+#    #+#              #
#    Updated: 2023/05/26 21:20:43 by ysalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CORE_SRC := builtins.c \
		cd.c \
		echo.c \
		env.c \
		export.c \
		pwd.c \
		setup.c \
		unset.c \
		exit.c \
		state.c \
		get_current_wd.c \
		get_env_var.c \
		set_env_var.c \
		get_env_arr.c \
		get_builtin.c \
		get_last_status.c \
		set_last_status.c \
		get_path.c \
		terminal.c \
		core.utils.c \

CORE_OBJ := $(CORE_SRC:%.c=%.o)
CORE_OBJ := $(addprefix obj/, $(CORE_OBJ))
