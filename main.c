#include "header.h"


void	print_map(t_map *mapo)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	map = mapo->map;
	while (map[0][i++])
		write(1, "*", 1);
	write(1, "\n", 1);
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (j < ft_strlen(map[i]))
		{
			write(1, &map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
void close_window(t_data *data, char *msg)
{
    t_map *mapo;

    mapo = data->mapo;
    mlx_destroy_window(data->mlx.mlx, data->mlx.win);
    free_map_exit(mapo->map, 0);
    printf("%s\n", msg);
    ft_free(mapo);
    exit(1);
}
int	 handle_input(int keysym, t_data *data)
{
	t_map	*mapo;
	mapo = data->mapo;
	if (keysym == XK_Escape)
        close_window(data, "clicked on esc key");
	if (keysym == XK_Up) // w
		move_up(data, mapo);
	if (keysym == XK_Down)
		move_down(data, mapo);
	if (keysym == XK_Right) // d
		move_right(data, mapo);
	if (keysym == XK_Left) // a
		move_left(data, mapo);
	if (mapo->map[mapo->py][mapo->px] != 'E')
		mapo->map[mapo->py][mapo->px] = 'P';
	return (0);
}


int	main(int ac, char *av[])
{
	t_data data;
	data.mlx.mlx = mlx_init();
	data.mlx.win = mlx_new_window(data.mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, ":v");
	data.mapo = malloc(sizeof(t_map));
    data.mapo->map = read_map("./map.ber");
    set_mapo(data.mapo);
    set_images(&data);
    verify(&data);
	// choof tv get images from there
    mlx_key_hook(data.mlx.win, handle_input, &data);
    mlx_loop_hook(data.mlx.mlx, draw, &data);
	mlx_loop(data.mlx.mlx);
    free_imgs_exit(data.imgs, 0);
    mlx_destroy_window(data.mlx.mlx, data.mlx.win);
}