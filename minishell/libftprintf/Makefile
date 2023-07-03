# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouda <plouda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 15:05:09 by plouda            #+#    #+#              #
#    Updated: 2023/07/03 10:32:47 by plouda           ###   ########.fr        #
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
	@make --no-print-directory -C $(LIBFT) bonus
	@cp libft/libft.a .
	@mv libft.a $(NAME)
	@$(AR) $(NAME) $^

.c.o:
	@$(GCC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	@rm -f $(OBJS)
	@make clean --no-print-directory -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@rm -f libft/libft.a

re: fclean all

.PHONY: all clean fclean re

