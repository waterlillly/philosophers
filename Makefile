CC = cc
CFLAGS = -Wall -Werror -Wextra -g

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

CFILES = src/main.c src/check_args.c src/init.c src/monitor.c src/time.c \
CFILES += src/print.c src/create.c src/routine.c src/exit.c src/early_exit.c \
CFILES += src/utils/ft_atoi_long.c src/utils/ft_itoa_long.c src/utils/ft_strcmp_bool.c \
CFILES += src/utils/ft_strdup.c src/utils/ft_strlen.c src/utils/ft_putstr_fd.c \
CFILES += src/utils/ft_putendl_fd.c src/utils/ft_putchar_fd.c src/utils/ft_strjoin.c \

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