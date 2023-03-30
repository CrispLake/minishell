# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 12:38:01 by emajuri           #+#    #+#              #
#    Updated: 2023/03/30 12:38:38 by emajuri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC = 

OSRC = $(SRC:%.c=%.o)

WWW = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OSRC)
	cc $(WWW) $(OSRC) -o $(NAME)

clean:
	rm -f $(OSRC)

fclean: clean
	rm -f $(NAME)

%.o: %.c
	cc $(WWW) -c -o $@ $^

re: fclean all
