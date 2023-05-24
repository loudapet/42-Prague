# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 15:05:09 by plouda            #+#    #+#              #
#    Updated: 2023/05/24 13:37:01 by plouda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRCS =	colors/colors.c \
		colors/palette.c \
		hooks/cursor.c \
		hooks/key_events_actions.c \
		hooks/key_events.c \
		hooks/reset_angles.c \
		hooks/resize.c \
		hooks/scroll.c \
		utils/allocate.c \
		utils/create_raster_utils.c \
		utils/free_items.c \
		utils/ft_atoi_base.c \
		utils/initialize.c \
		utils/parse_map_utils.c \
		utils/utils_num.c \
		utils/utils.c \
		project/create_raster.c \
		project/main.c \
		project/parse_map.c \
		project/print_instructions.c \
		project/project_core.c \
		project/project.c \
		project/projections.c \
		project/rotations.c \
		project/vectors.c

BUILD_DIR = ./obj
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS))
OBJS := $(OBJS:%.c=%.o)
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

LIBFTPRINTF = libftprintf
AR = ar rc
GCC = gcc -Wall -Wextra -Werror

HEADERS = -I ./include -I $(MLX_DIR)/include
MLX_DIR = ./lib/MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm -Ofast
MLX_FLAGS = -ldl -lglfw -pthread -lm
COMPILER_SPEC = -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTPRINTF)
	mv libftprintf/libftprintf.a .
	$(GCC) $(OBJS) $(LIBFTPRINTF).a $(MLX_LIB) -o $(NAME)

obj/%.o: src/%.c | objdir
	$(GCC) -c $^ $(HEADERS) -o $@

objdir:
	mkdir -p obj
	mkdir -p obj/colors
	mkdir -p obj/utils
	mkdir -p obj/hooks
	mkdir -p obj/project

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

