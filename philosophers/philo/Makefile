# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouda <plouda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 10:27:43 by plouda            #+#    #+#              #
#    Updated: 2023/05/26 11:08:19 by plouda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = test.c

BUILD_DIR = ./build
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS))
OBJS := $(OBJS:%.c=%.o)

GCC = gcc -Wall -Wextra -Werror -lpthread

HEADERS = -I ./philo.h

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