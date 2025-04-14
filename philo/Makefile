.DEFAULT_GOAL := all

CFLAGS = -Wall -Werror -Wextra -pthread

NAME = philo
SRC_DIR = srcs
INCLUDE = -I includes

SRCS = $(shell find $(SRC_DIR) -maxdepth 1 -name "*.c")

OBJS = $(SRCS:.c=.o)


%.o: %.c
	cc $(CFLAGS) $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
