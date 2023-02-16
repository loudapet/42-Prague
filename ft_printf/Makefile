# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 15:05:09 by plouda            #+#    #+#              #
#    Updated: 2023/02/16 11:39:50 by plouda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_printf.c ft_printf_char.c ft_printf_hex.c ft_printf_nbr.c \
		ft_printf_ptr.c ft_printf_str.c ft_printf_unbr.c ft_uitoa.c \
		ft_flag_handler.c

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

bonus: all

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

.PHONY: all clean fclean re

