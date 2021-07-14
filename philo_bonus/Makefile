NAME = philo_bonus

SRC = main.c utils.c exit.c init.c print_state.c philosopher.c monitoring.c

DIR = ./srcs/

SRCS = $(addprefix $(DIR), $(SRC))

HEADER = includes

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