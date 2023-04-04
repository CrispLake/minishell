# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 12:38:01 by emajuri           #+#    #+#              #
#    Updated: 2023/04/04 13:47:00 by emajuri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC = $(NAME).c print_error.c

OSRC = $(addprefix obj/,$(SRC:%.c=%.o))

DEP = $(OSRC:%.o=%.d)

#folders
INC = ./inc

#libft

LIBFT = libft/libft.a
LIBFT_FLAGS = -L libft -lft

#flags
READLINE_FLAGS = -lreadline -L $(HOME)/.brew/Cellar/readline/8.2.1/lib
WWW = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OSRC) $(LIBFT)
	cc $(WWW) $(OSRC) -o $(NAME) $(READLINE_FLAGS) $(LIBFT_FLAGS)

clean:
	rm -f $(OSRC) $(DEP)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

-include $(DEP)

obj/%.o: src/%.c
	cc $(WWW) -MMD -c $< -o $@

re: fclean all
