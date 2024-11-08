CC = cc
CFLAGS = -Wall -Werror -Wextra -g

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

CFILES = main.c check_args.c init.c monitor.c time.c print.c create.c routine.c exit.c early_exit.c
CFILES += utils/ft_atoi_long.c utils/ft_itoa_long.c utils/ft_strcmp_bool.c utils/ft_strdup.c utils/ft_strlen.c utils/ft_putstr_fd.c utils/ft_putendl_fd.c utils/ft_putchar_fd.c utils/ft_strjoin.c
OFILES = $(CFILES:.c=.o)
NAME = philo

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) -o $@ $^ -pthread

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re