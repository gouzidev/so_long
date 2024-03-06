CC = cc
AR = ar -rcs
NAME = so_long
ARCHIVE = so_long.a
FLAGS = -Wall -Werror -Wextra
SRCS = map.c main.c draw.c verify.c verify1.c flood1.c flood2.c helper1.c helper2.c move.c str.c gnl1.c gnl2.c free.c itoa.c draw1.c draw2.c ft_printf.c ft_printf1.c ft_printf2.c animate.c

OBJS = $(SRCS:.c=.o)

ARGS =  -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(ARCHIVE)
	$(CC) $(FLAGS) $(ARGS) -I$(ARCHIVE) -o $(NAME) $(ARCHIVE)

$(ARCHIVE): $(OBJS)
	$(AR) $@ $?

%.o:%.c
	$(CC) $(FLAGS) -c $? -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all