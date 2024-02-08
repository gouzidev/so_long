#include "header.h"
void set_images(t_data *data)
{
	int			img_w;
	int			img_h;

	data->imgs = malloc(sizeof(t_assets));
	data->imgs->wall_img = mlx_xpm_file_to_image(data->mlx.mlx, "./assets/wall.xpm", &img_w, &img_h);
	data->imgs->floor_img = mlx_xpm_file_to_image(data->mlx.mlx, "./assets/floor.xpm", &img_w, &img_h);
	data->imgs->exit_img = mlx_xpm_file_to_image(data->mlx.mlx, "./assets/exit.xpm", &img_w, &img_h);
	data->imgs->player_img = mlx_xpm_file_to_image(data->mlx.mlx, "./assets/p1.xpm", &img_w, &img_h);
	data->imgs->coin_img = mlx_xpm_file_to_image(data->mlx.mlx, "./assets/coin.xpm", &img_w, &img_h);
}
int	print_exit(char *msg, int exit_msg)
{
	printf("%s", msg);
	exit(exit_msg);
}
void	set_mapo(t_map *mapo)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = mapo->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				mapo->cc++;
			if (map[i][j] == 'P')
			{
				mapo->py = i;
				mapo->px = j;
			}
			j++;
		}
		i++;
	}
	mapo->h = i;
	mapo->w = j;
}
void set_up_data_struct(t_data *data, t_img img, t_mlx mlx, t_map *mapo)
{
	data->img = img;
	data->mlx = mlx;
	data->mapo = mapo;
}
void	set_px_py(t_map *mapo, int i, int j)
{
	mapo->px = j;
	mapo->py = i;
}