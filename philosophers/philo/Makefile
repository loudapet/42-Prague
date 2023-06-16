# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouda <plouda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 10:27:43 by plouda            #+#    #+#              #
#    Updated: 2023/06/16 12:04:40 by plouda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS =	philo.c \
		utils.c \
		inits.c \
		eat_sleep_think.c

BUILD_DIR = ./build
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS))
OBJS := $(OBJS:%.c=%.o)

GCC = gcc -Wall -Wextra -Werror -lpthread

HEADERS = -I ../philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(GCC) $(OBJS) -o $(NAME)

build/%.o: %.c | objdir
	$(GCC) -c $^ $(HEADERS) -o $@

objdir:
	mkdir -p build

clean:
	rm -rf ./build

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, bonus