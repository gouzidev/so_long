#include "header.h"

int	draw_map(t_data *data)
{
	t_map		*mapo;
	draw_map_images(data->mapo, data, data->imgs);
	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	mlx_destroy_image(data->mlx.mlx, data->img.img);
	return (0);
}
