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

void close_window(t_data *data)
{
    t_map *mapo;

    mapo = data->mapo;
    mlx_destroy_window(data->mlx.mlx, data->mlx.win);
    free_map_exit(mapo->map, 0);
    ft_free(mapo);
    exit(1);
}
int	 handle_input(int keysym, t_data *data)
{
	t_map	*mapo;
	mapo = data->mapo;
	if (keysym == XK_Escape)
        close_window(data);
	if (keysym == XK_Up) // w
		move_player(data, mapo, 0);
	if (keysym == XK_Down)
		move_player(data, mapo, 2);
	if (keysym == XK_Right) // d
		move_player(data, mapo, 1);
	if (keysym == XK_Left) // a
		move_player(data, mapo, 3);
	if (mapo->map[mapo->py][mapo->px] != 'E')
		mapo->map[mapo->py][mapo->px] = 'P';
	return (0);
}
void	draw_map_images(t_map *mapo, t_data *data, t_assets *images)
{
	int	i;
	int	j;
	i = -1;
	while (++i < mapo->h)
	{
		j = -1;
		while (++j < mapo->w)
		{
			if (mapo->map[i][j] == '1')
				mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
					images->wall_img, j * 50, i * 50);
			else if (mapo->map[i][j] == '0')
				mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
					images->floor_img, j * 50, i * 50);
			else if (mapo->map[i][j] == 'P')
			{
				set_px_py(mapo, i, j);
				mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
					images->player_img, j * 50, i * 50);
			}
			else if (mapo->map[i][j] == 'E')
				mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
					images->exit_img, j * 50, i * 50);
			else if (mapo->map[i][j] == 'C')
				mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
					images->coin_img, j * 50, i * 50);
			else
				print_exit("bad map (invalid character)\n", 1);
		}
	}
}
int draw(t_data *data)
{
    draw_map_images(data->mapo, data, data->imgs);
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