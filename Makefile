CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=thread
RM = rm -f

SRC =  mandatory/init.c  mandatory/philo.c mandatory/manage.c  mandatory/thread.c  mandatory/utils.c mandatory/helper_thread.c\

OBJ = $(SRC:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -pthread

mandatory/%.o: mandatory/%.c include/philo.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all