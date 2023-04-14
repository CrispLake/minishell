# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 12:38:01 by emajuri           #+#    #+#              #
#    Updated: 2023/04/13 17:47:45 by emajuri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = $(NAME).c print_error.c tokenization.c tokenization_helpers.c \
	  sig_handler.c count_quotes.c

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
