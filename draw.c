#include "header.h"
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
int	draw_map(t_data *data)
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		*mapo;

	img = data->img;
	mlx = data->mlx.mlx;
	win = data->mlx.win;
	if (img.img == NULL)
		print_exit("problem in img\n", 1);
	set_images(data);
	mapo = data->mapo;
	mapo->cc = 0;
	set_mapo(mapo);
	verify_borders(mapo);
	data->img.img = mlx_new_image(data->mlx.mlx, 500, 500);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	draw_map_images(mapo, data, data->imgs);
	return (0);
}
