# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 15:05:09 by plouda            #+#    #+#              #
#    Updated: 2023/03/13 14:56:02 by plouda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	op_swap.c op_push.c op_rotate.c op_reverse_rotate.c \
		count_moves.c count_moves_utils.c get_cheapest_nbr.c \
		push_value.c sort_3.c push_value_back.c print_error.c \
		utils.c validators.c create_stacks.c clist_utils_2.c \
		count_rotas.c push_value_flags.c rotate_lowest_up.c \
		clist_utils.c clist_print.c parse_arguments.c
DIR = ./

NAME = push_swap
MAIN = main.c
SRCS = $(addprefix $(DIR), $(SRC) $(MAIN))
OBJS = $(SRCS:.c=.o)

CHECKER = checker
MAIN_CHECKER = checker_bonus.c
SRC_CHECKER = execute_instructions_bonus.c
SRCS_CHECKER = $(addprefix $(DIR), $(SRC) $(SRC_CHECKER) $(MAIN_CHECKER))
OBJS_CHECKER = $(SRCS_CHECKER:.c=.o)

LIBFTPRINTF = libftprintf
AR = ar rc
GCC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME) bonus

$(NAME): $(OBJS)
	make -C $(LIBFTPRINTF)
	mv libftprintf/libftprintf.a .
	$(GCC) $(CFLAGS) $(OBJS) $(LIBFTPRINTF).a -o $(NAME)

bonus: $(CHECKER)

$(CHECKER): $(OBJS_CHECKER)
	make -C $(LIBFTPRINTF)
	mv libftprintf/libftprintf.a .
	$(GCC) $(CFLAGS) $(OBJS_CHECKER) $(LIBFTPRINTF).a -o $(CHECKER)

.c.o:
	$(GCC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_CHECKER)
	make clean -C $(LIBFTPRINTF)

fclean: clean
	rm -f $(NAME) $(CHECKER)
	rm -f libftprintf.a
	rm -f libftprintf/libft/libft.a

re: fclean all

.PHONY: all clean fclean re

