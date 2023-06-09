# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 12:38:01 by emajuri           #+#    #+#              #
#    Updated: 2023/05/02 18:54:42 by emajuri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = $(NAME).c tokenization.c tokenization_helpers.c sig_handler.c \
	  count_quotes.c init_env.c make_commands.c make_commands_helpers.c \
	  helper_functions.c builtin_env.c builtin_pwd.c builtin_export.c \
	  builtin_unset.c execute_cmds.c make_fd.c builtin_echo.c builtin_exit.c \
	  builtin_cd.c add_filepath.c execute_cmds_helpers.c execute_builtins.c \
	  expand_variables.c expand_variables_helpers.c remove_empty.c \
	  check_for_env_duplicates.c

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
