# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouda <plouda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 15:05:09 by plouda            #+#    #+#              #
#    Updated: 2023/05/15 13:33:04 by plouda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
OBJS = obj/line.o obj/utils.o obj/parse_map.o obj/vectors.o obj/projections.o \
		obj/free_items.o obj/map_dimension_utils.o obj/main.o obj/rotations.o \
		obj/camera.o obj/hooks.o

LIBFTPRINTF = libftprintf
AR = ar rc
GCC = gcc -Wall -Wextra -Werror

HEADERS = -I ./include -I $(MLX_DIR)/include
MLX_DIR = ./lib/MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
MLX_FLAGS = -ldl -lglfw -pthread -lm
COMPILER_SPEC = -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTPRINTF)
	mv libftprintf/libftprintf.a .
	$(GCC) $(OBJS) $(LIBFTPRINTF).a $(MLX_LIB) -o $(NAME)

obj/%.o: src/%.c
	mkdir -p obj
	$(GCC) -c $< $(HEADERS) -o $@

$(MLX_LIB):
	cmake $(MLX_DIR) $(COMPILER_SPEC) -B $(MLX_DIR)/build
	make -C $(MLX_DIR)/build -j4
	
clean:
	rm -rf ./obj
	make clean -C $(LIBFTPRINTF)
	rm -rf $(MLX_DIR)/build

fclean: clean
	rm -f $(NAME)
	rm -f libftprintf.a
	rm -f libftprintf/libft/libft.a

re: fclean all

.PHONY: all, clean, fclean, re, bonus

