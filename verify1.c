#include "header.h"

void verify_exit_count(t_data *data)
{
	int i;
	int j;
	int exit_count;

	i = 0;
	exit_count = 0;
	i = 0;
	while (data->mapo->map[i])
	{
		j = 0;
		while (data->mapo->map[i][j])
		{
			if (data->mapo->map[i][j] == 'E')
			{
				if (++exit_count > 1)
					close_window(data);
			}
			j++;
		}
		i++;
	}
}

void	verify(t_data *data)
{
	char	**map_copy;
	int		r;
	t_map *mapo;

	mapo = data->mapo;
	verify_borders(mapo);
	verify_exit_count(data);
	map_copy = copy_map(mapo->map, mapo->w, mapo->h);
	if (map_copy == NULL)
		close_window(data);
	r = verify_exit(map_copy, mapo->w, mapo->h, mapo->py, mapo->px);
	if (r == 1)
	{
		close_window(data);
		print_exit("no exit\n", 1);
	}
	free_map_exit(map_copy, 0);
}


void	verify_borders(t_map *mapo)
{
	int		i;
	int		w;
	int		h;
	char	**map;

	i = 0;
	map = mapo->map;
	w = mapo->w;
	h = mapo->h;
	while (i < w)
	{
		if (map[0][i] != '1' || map[h - 1][i] != '1')
			print_exit("bad map borders\n", 1);
		i++;
	}
	i = 0;
	while (i < h)
	{
		if (map[i][0] != '1' || map[i][w - 1] != '1')
			print_exit("bad map borders\n", 1);
		i++;
	}
}
int	verify_exit(char **map, int w, int h, int py, int px)
{
	int	r;

	r = 1;
	if (map[py][px] == 'E')
		return (0);
	if (map[py][px] == 'x')
		return (1);
	map[py][px] = 'x';
	if (py - 1 >= 1 && map[py - 1][px] != '1' && map[py - 1][px] != 'x')
	{
		r = verify_exit(map, w, h, py - 1, px);
		if (r == 0)
			return (r);
	}
	if (px + 1 < w - 1 && map[py][px + 1] != '1' && map[py][px + 1] != 'x')
	{
		r = verify_exit(map, w, h, py, px + 1);
		if (r == 0)
			return (r);
	}
	if (px - 1 >= 1 && map[py][px - 1] != '1' && map[py][px - 1] != 'x')
	{
		r = verify_exit(map, w, h, py, px - 1);
		if (r == 0)
			return (r);
	}
	if (py + 1 < h - 1 && map[py + 1][px] != '1' && map[py + 1][px] != 'x')
	{
		r = verify_exit(map, w, h, py + 1, px);
		if (r == 0)
			return (r);
	}
	return (r);
}