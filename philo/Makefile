# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ukim <ukim@42seoul.kr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 00:05:21 by seapark           #+#    #+#              #
#    Updated: 2021/07/15 00:07:34 by ukim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c utils.c exit.c init.c print_state.c philosopher.c

DIR = ./srcs/
uimuim42oulk         
SRCS = $(addprefix $(DIR), $(SRC))

HEADER = includes706uim   

CC = gcc

CFLAG = -Wall -Wextra -Werror

IPTHREAD= -lpthread

OBJ = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAG) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
		@$(CC) -g $(CFLAG) $(OBJ) -o $@

clean:
		@/bin/rm -rf $(OBJ)

fclean:
		@/bin/rm -rf $(OBJ)
		@/bin/rm -f $(NAME)

re: fclean all