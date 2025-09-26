NAME = so_long

SRCS = map.c main.c draw.c verify.c verify1.c flood1.c flood2.c helper1.c helper2.c move.c str.c gnl1.c gnl2.c free.c itoa.c draw1.c draw2.c ft_printf.c ft_printf1.c ft_printf2.c animate.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I/usr/include -Iminilibx_copy

CC = gcc

# Use the prebuilt MiniLibX shipped in minilibx_copy
MLX_LIB = ./minilibx_copy/libmlx_Linux.a
# Link with X11 and extensions required by libmlx on Linux
MLX_FLAGS = $(MLX_LIB) -lXext -lX11 -lXrender -lXfixes -lXi -lXinerama -lm -lz -lbsd

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

clean:
	rm -f $(OBJS) $(ARCHIVE)

fclean: clean
	rm -f $(NAME)

re: fclean all
