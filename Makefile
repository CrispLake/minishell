# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 12:38:01 by emajuri           #+#    #+#              #
#    Updated: 2023/04/07 21:24:01 by jole             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = $(NAME).c print_error.c sig_handler.c count_quotes.c expand_variables.c

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

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	cc $(WWW) $(OBJ) -o $(NAME) $(READLINE_FLAGS) $(LIBFT_FLAGS)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

-include $(DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	cc $(WWW) -MMD -c $< -o $@

re: fclean all
