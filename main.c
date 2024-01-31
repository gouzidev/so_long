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
void	print_map(t_map mapo)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	map = mapo.map;
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
int	handle_input(int keysym, t_data *data)
{
	t_map	*mapo;

	mapo = data->mapo;
	set_mapo(data->mapo);
	if (keysym == 53)
	{
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		free_map_exit(mapo->map, 0);
		ft_free(mapo);
		system("leaks a.out");
		exit(1);
	}
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
int	main(int ac, char *av[])
{
	// choof tv get images from there
	t_map *mapo;
	t_mlx mlx;
	t_img img;
	t_data data;
	char **map;

	verify_map_name(ac, av);
	map = read_map(av[1]);

	mapo = malloc(sizeof(t_map));
	mapo->map = map;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, ":v");
	img.img = mlx_new_image(mlx.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	set_up_data_struct(&data, img, mlx, mapo);
	verify(&data);
	mlx_key_hook(mlx.win, handle_input, &data);
	mlx_loop_hook(mlx.mlx, draw_map, &data);
	mlx_loop(mlx.mlx);
	system("leaks a.out");
}