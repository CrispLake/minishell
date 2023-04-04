# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 12:38:01 by emajuri           #+#    #+#              #
#    Updated: 2023/04/04 13:55:18 by emajuri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC = $(NAME).c print_error.c

OBJ = $(addprefix obj/,$(SRC:%.c=%.o))

DEP = $(OBJ:%.o=%.d)

#folders
INC = ./inc
FT_DIR = ./libft
SRC_DIR = ./src
OBJ_DIR = ./obj

#libft

LIBFT = $(FT_DIR)/libft.a
LIBFT_FLAGS = -L $(FT_DIR) -lft

#flags
READLINE_FLAGS = -lreadline -L $(HOME)/.brew/Cellar/readline/8.2.1/lib
WWW = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) $(LIBFT)
	cc $(WWW) $(OBJ) -o $(NAME) $(READLINE_FLAGS) $(LIBFT_FLAGS)

clean:
	rm -f $(OBJ) $(DEP)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

-include $(DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	cc $(WWW) -MMD -c $< -o $@

re: fclean all
