# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 15:05:09 by plouda            #+#    #+#              #
#    Updated: 2023/01/31 12:44:21 by plouda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_printf.c main.c

SRCS = $(addprefix $(DIR), $(SRC))
OBJS = $(SRCS:.c=.o)
DIR = ./

NAME = libftprintf.a
LIBFT = libft
AR = ar rc
GCC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT)
	cp libft/libft.a .
	mv libft.a $(NAME)
	$(AR) $(NAME) $^

.c.o: $(SRCS)
	$(GCC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

.PHONY: all clean fclean re

