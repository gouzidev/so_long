#include "header.h"

void draw_map_images(t_map *mapo, t_data *data, t_assets *images)
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