# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/08 11:15:44 by ulefebvr          #+#    #+#              #
#    Updated: 2016/12/13 14:42:55 by rclanget         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ_PATH	=	./obj/
SRC_PATH	=	./srcs/


NAME		= libft.a
SRC_NAME	= 	ft_putchar.c ft_putstr.c ft_putnbr.c ft_strlen.c ft_strdup.c \
				ft_atoi.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_tolower.c \
				ft_toupper.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isprint.c \
				ft_isascii.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
				ft_memmove.c ft_memchr.c ft_memcmp.c ft_strcmp.c ft_strncmp.c \
				ft_strstr.c ft_strnstr.c ft_strchr.c ft_strrchr.c ft_strlcat.c \
				ft_memdel.c ft_memalloc.c ft_strnew.c ft_strdel.c ft_strclr.c \
				ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
				ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
				ft_itoa.c ft_putendl.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c ft_strncat.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c \
				ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_nbrlen.c ft_print.c\
				get_next_line.c ft_getenv.c ft_option.c ft_free_them_all.c\
				ft_strrstr.c
SRC			= $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ_NAME	= $(SRC_NAME:.c=.o)
OBJ			= $(addprefix $(OBJ_PATH),$(OBJ_NAME))
CMP		= gcc
FLAGS	= -Wall -Werror -Wextra


all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CMP) $(FLAGS) -I ./includes -o $@ -c $<

.PHONY: clean fclean re

clean:
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean
	@rm -fv $(NAME)

re: fclean all

norme:
	norminette $(SRC)
