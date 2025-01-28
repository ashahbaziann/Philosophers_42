NAME = philo

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRCS = main.c\
		utils.c\
		validate.c\
		init.c\
		wrappers.c\
		set_get.c\
		simulation.c\
		print.c\


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) philo.h
	cc $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
