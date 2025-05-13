NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = main.c \
		init_sim.c \
		start_sim.c \
		philo_routine.c \
		philo_actions.c \
		monitor_sim.c \
		cleanup_and_error.c \
		atoi.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
