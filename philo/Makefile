CC = gcc
FLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3
NAME = philo
SRC =	main.c \
		parse.c \
		routine.c \
		utils.c \
		threads.c

OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all