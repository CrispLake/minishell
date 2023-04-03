# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 12:38:01 by emajuri           #+#    #+#              #
#    Updated: 2023/04/03 20:24:13 by emajuri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

LIBFT = libft/libft.a

SRC = $(NAME).c print_error.c tokenization.c

OSRC = $(SRC:%.c=%.o)

WWW = -Wall -Wextra -Werror

LIBFT_FLAGS = -L libft -lft

READLINE_FLAGS = -lreadline -L $(HOME)/.brew/Cellar/readline/8.2.1/lib

.PHONY: all clean fclean re

all: $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OSRC) $(LIBFT)
	cc $(WWW) $(OSRC) -o $(NAME) $(READLINE_FLAGS) $(LIBFT_FLAGS)

clean:
	rm -f $(OSRC)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

%.o: %.c
	cc $(WWW) -c -o $@ $^

re: fclean all
