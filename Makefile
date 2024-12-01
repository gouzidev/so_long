NAME = so_long

SRCS = map.c main.c draw.c verify.c verify1.c flood1.c flood2.c helper1.c helper2.c move.c str.c gnl1.c gnl2.c free.c itoa.c draw1.c draw2.c ft_printf.c ft_printf1.c ft_printf2.c animate.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I/usr/include -Imlx


MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_linux.a
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

all: $(MLX_LIB) $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

$(MLX_LIB):
	@make -C $(MLX_DIR)


clean:
	rm -f $(OBJS) $(ARCHIVE)

fclean: clean
	rm -f $(NAME)

re: fclean all
