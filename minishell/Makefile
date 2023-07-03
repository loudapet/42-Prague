# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouda <plouda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 15:05:09 by plouda            #+#    #+#              #
#    Updated: 2023/07/03 12:01:50 by plouda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS =	project/main.c

BUILD_DIR = ./obj
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS))
OBJS := $(OBJS:%.c=%.o)
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

LIBFTPRINTF = libftprintf
AR = ar rc
CC = cc -Wall -Wextra -Werror
FLAGS = -lreadline

HEADERS = -I ./include/

# Colors (credits to xhelp00)
GREEN		=	$(shell printf "\033[0;32m")
YELLOW		=	$(shell printf "\033[0;33m")
RESET		=	$(shell printf "\033[0m")

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@make --no-print-directory -C $(LIBFTPRINTF)
	@mv libftprintf/libftprintf.a .
	@echo "$(YELLOW)Linking objects...$(RESET)"
	@$(CC) $(FLAGS) $(OBJS) $(LIBFTPRINTF).a -o $(NAME)
	@echo "$(GREEN)Compilation successful.$(RESET)"

obj/%.o: src/%.c | objdir
	@$(CC) -c $^ $(HEADERS) -o $@

objdir:
	@mkdir -p obj
	@mkdir -p obj/project

clean:
	@echo "$(YELLOW)Removing object files...$(RESET)"
	@rm -rf ./obj
	@make clean --no-print-directory -C $(LIBFTPRINTF)

fclean: clean
	@echo "$(YELLOW)Removing executable...$(RESET)"
	@rm -f $(NAME)
	@rm -f libftprintf.a
	@rm -f libftprintf/libft/libft.a

re: fclean all

.PHONY: all, clean, fclean, re, bonus

