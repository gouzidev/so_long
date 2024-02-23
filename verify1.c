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
					close_window(data, "more than one door !");
			}
			j++;
		}
		i++;
	}
}

int check_cc(int **cc_arr)
{
	int i;

	i = 0;
	while (cc_arr[i])
	{
		printf("  ->  [%d][%d] => %d\n", cc_arr[i][0], cc_arr[i][1], cc_arr[i][2]);
		if (cc_arr[i][2] == 0)
			return 1;
		i++;
	}
	return 0;
}


void	verify(t_data *data)
{
	char	**map_copy;
	int		r;
	t_map *mapo;
	int **cc_arr;
	mapo = data->mapo;
	verify_borders(mapo);
	verify_exit_count(data);
	map_copy = copy_map(mapo->map, mapo->w, mapo->h);
	if (map_copy == NULL)
		close_window(data, "cant malloc map copy");
	r = verify_exit(map_copy, mapo->w, mapo->h, mapo->py, mapo->px);
	if (r == 1)
		close_window(data, "no exit");
	free_map_exit(map_copy, 0);
	cc_arr = make_cc_arr(mapo->map, mapo->w, mapo->h, mapo->cc);

	map_copy = copy_map(mapo->map, mapo->w, mapo->h);
	r = verify_cc(cc_arr, map_copy, mapo->w, mapo->h, mapo->py, mapo->py, mapo->cc);
	check_cc(cc_arr);

	free_cc_arr(cc_arr);
	free_map_exit(map_copy, 0);

	if (r == 1)
		close_window(data, "cant find all collectables");
}
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
int verify_cc(int **cc_arr, char **map, int w, int h, int py, int px, int cc)
{
    int r = 1;
	if (check_cc(cc_arr) == 1)
		return 0;
    if (map[py][px] == 'C' && cc-- > 0)
		cc_arr[--cc][2] = 1;

    if (cc == 0)
        return 0;
    if (map[py][px] == 'x')
        return 1;
    if (py - 1 >= 1 && map[py - 1][px] != '1' && map[py - 1][px] != 'x')
    {
        map[py][px] = 'x';
        r = verify_cc(cc_arr, map, w, h, py - 1, px, cc);
        if (r == 0)
            return r;
    }
    if (px + 1 < w - 1 && map[py][px + 1] != '1' && map[py][px + 1] != 'x')
    {
        map[py][px] = 'x';
        r = verify_cc(cc_arr, map, w, h, py, px + 1, cc);
        if (r == 0)
            return r;
    }
    if (px - 1 >= 1 && map[py][px - 1] != '1' && map[py][px - 1] != 'x')
    {
        map[py][px] = 'x';
        r = verify_cc(cc_arr, map, w, h, py, px - 1, cc);
        if (r == 0)
            return r;
    }
    if (py + 1 < h - 1 && map[py + 1][px] != '1' && map[py + 1][px] != 'x')
    {
        map[py][px] = 'x';
        r = verify_cc(cc_arr, map, w, h, py + 1, px, cc);
        if (r == 0)
            return r;
    }
    return r;
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