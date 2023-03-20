# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 15:05:09 by plouda            #+#    #+#              #
#    Updated: 2023/03/20 15:09:18 by plouda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = pipex.c print_error.c process_command.c free.c
DIR = ./

NAME = pipex
SRCS = $(addprefix $(DIR), $(SRC))
OBJS = $(SRCS:.c=.o)

LIBFTPRINTF = libftprintf
AR = ar rc
GCC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTPRINTF)
	mv libftprintf/libftprintf.a .
	$(GCC) $(CFLAGS) $(OBJS) $(LIBFTPRINTF).a -o $(NAME)

bonus: all

.c.o:
	$(GCC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFTPRINTF)

fclean: clean
	rm -f $(NAME)
	rm -f libftprintf.a
	rm -f libftprintf/libft/libft.a

re: fclean all

.PHONY: all clean fclean re

