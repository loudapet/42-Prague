# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 15:05:09 by plouda            #+#    #+#              #
#    Updated: 2023/03/31 17:26:37 by plouda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = pipex.c process_command.c free.c print_error.c 
BONUS_SRC = pipex_bonus.c process_command_bonus.c \
			free_bonus.c print_error_bonus.c \
			pipex_utils_bonus.c f_pipex_multiple_utils_bonus.c
DIR = ./src/
BONUS_DIR = ./bonus_src/

NAME = pipex
SRCS = $(addprefix $(DIR), $(SRC))
OBJS = $(SRCS:.c=.o)
BONUS_SRCS = $(addprefix $(BONUS_DIR), $(BONUS_SRC))
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

LIBFTPRINTF = libftprintf
AR = ar rc
GCC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTPRINTF)
	mv libftprintf/libftprintf.a .
	$(GCC) $(CFLAGS) $(OBJS) $(LIBFTPRINTF).a -o $(NAME)

bonus: $(BONUS_OBJS)
	make -C $(LIBFTPRINTF)
	mv libftprintf/libftprintf.a .
	$(GCC) $(CFLAGS) $(BONUS_OBJS) $(LIBFTPRINTF).a -o $(NAME)

.c.o:
	$(GCC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	make clean -C $(LIBFTPRINTF)

fclean: clean
	rm -f $(NAME)
	rm -f libftprintf.a
	rm -f libftprintf/libft/libft.a

re: fclean all

.PHONY: all clean fclean re bonus

