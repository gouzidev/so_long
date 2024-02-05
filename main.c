#include "header.h"


int **make_cc_arr(char **map, int w, int h, int cc)
{
    int i;
    int j;
    int **arr;
    int ccc;
    ccc = cc;
    arr = malloc((cc + 1) * sizeof(char *));
    // arr =>   [[x, y, 0]]

    i = 1;
    ccc = 0;
    while (i < h - 1)
    {
        j = 1;
        while (j < w - 1)
        {
            if (map[i][j] == 'C')
            {
                arr[ccc] = malloc(3 * sizeof(int));
                arr[ccc][0] = i;
                arr[ccc][1] = j;
                arr[ccc][2] = 0;
                ccc++;
            }
            j++;
        }
        i++;
    }
    arr[ccc] = NULL;
    
    return arr;
}
int verify_cc(char **map, int w, int h, int py, int px)
{
    int r = 1;
    if (map[py][px] == 'E')
        return 0;
    if (map[py][px] == 'x')
        return 1;
    if (py - 1 >= 1 && map[py - 1][px] != '1' && map[py - 1][px] != 'x')
    {
        map[py][px] = 'x';
        r = verify_exit(map, w, h, py - 1, px);
        if (r == 0)
            return r;
    }
    if (px + 1 < w - 1 && map[py][px + 1] != '1' && map[py][px + 1] != 'x')
    {
        map[py][px] = 'x';
        r = verify_exit(map, w, h, py, px + 1);
        if (r == 0)
            return r;
    }
    if (px - 1 >= 1 && map[py][px - 1] != '1' && map[py][px - 1] != 'x')
    {
        map[py][px] = 'x';
        r = verify_exit(map, w, h, py, px - 1);
        if (r == 0)
            return r;
    }
    if (py + 1 < h - 1 && map[py + 1][px] != '1' && map[py + 1][px] != 'x')
    {
        map[py][px] = 'x';
        r = verify_exit(map, w, h, py + 1, px);
        if (r == 0)
            return r;
    }
    return r;
}
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
    system("leaks a.out");
    exit(1);
}
int	 handle_input(int keysym, t_data *data)
{
	t_map	*mapo;
	mapo = data->mapo;
	if (keysym == 53)
        close_window(data);
	if (keysym == 13) // w
		move_player(data, mapo, 0);
	if (keysym == 1) // s
		move_player(data, mapo, 2);
	if (keysym == 2) // d
		move_player(data, mapo, 1);
	if (keysym == 0) // a
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
    printf("runned\n");
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