
NAME := libft.a

CC := cc

FLAGS := -Wall -Wextra -Werror

SRC :=	ft_atoi.c	\
		ft_bzero.c	\
		ft_calloc.c	\
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memmove.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strcmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		split.c \
		ft_toupper.c

BONUS = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstlast.c \
		ft_lstsize.c \
		ft_lstadd_back.c \
		ft_lstdelone.c 

OBJBONUS := $(BONUS:.c=.o)

OBJ := $(SRC:.c=.o)
RM = rm -f

all: $(NAME)

%.o:%.c 
	gcc $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
		ar -rcs $(NAME) $(OBJ)

bonus :$(OBJBONUS) $(OBJ)
		ar -rcs $(NAME) $(OBJBONUS)

clean: 
	${RM} ${OBJ} ${OBJBONUS}

fclean: clean
	${RM} $(NAME)

re: fclean all

.PHONY: all clean fclean re

 



