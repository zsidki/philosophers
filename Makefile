# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zsidki <zsidki@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 20:57:42 by zsidki            #+#    #+#              #
#    Updated: 2021/12/18 18:23:35 by zsidki           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all fclean clean re
CC = gcc
flags = -Wall -Wextra -Werror #-g -fsanitize=address
SRCS = main.c
NAME  = philo_one

all : $(NAME)

$(NAME): ${SRCS}
	@$(CC) $(flags) $(SRCS) -lpthread -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean: clean

re: fclean all

push:
	@git add .
	@git commit -m "$(m)"
	@git push origin main
