# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 15:05:09 by plouda            #+#    #+#              #
#    Updated: 2023/03/06 16:55:23 by plouda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = clist_utils.c clist_print.c main.c  \
		op_swap.c op_push.c op_rotate.c op_reverse_rotate.c \
		count_moves.c count_moves_utils.c get_cheapest_nbr.c \
		push_value.c sort_3.c push_value_back.c print_error.c \
		utils.c validators.c create_stacks.c clist_utils_2.c \
		count_rotas.c push_value_flags.c
SRCS = $(addprefix $(DIR), $(SRC))
OBJS = $(SRCS:.c=.o)
DIR = ./

NAME = push_swap
LIBFTPRINTF = libftprintf
AR = ar rc
GCC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTPRINTF)
	mv libftprintf/libftprintf.a .
	$(GCC) $(CFLAGS) $(OBJS) $(LIBFTPRINTF).a -o $(NAME)

.c.o: $(SRCS)
	$(GCC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFTPRINTF)

fclean: clean
	rm -f $(NAME)
	rm -f libftprintf.a
	rm -f libftprintf/libft/libft.a

re: fclean all

.PHONY: all clean fclean re

