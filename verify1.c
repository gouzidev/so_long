/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:40:17 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/05 22:15:50 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	verify_exit_count(t_data *data)
{
	int	i;
	int	j;
	int	exit_count;

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

void	verify_enemy_count(t_data *data)
{
	int	i;
	int	j;
	int	enemy_count;

	i = 0;
	enemy_count = 0;
	i = 0;
	while (data->mapo->map[i])
	{
		j = 0;
		while (data->mapo->map[i][j])
		{
			if (data->mapo->map[i][j] == 'N')
			{
				if (++enemy_count > 1)
					close_window(data, "more than one enemy !");
			}
			j++;
		}
		i++;
	}
	if (j < 3 || i < 3)
		close_window(data, "map too small \n");
}

void	verify_map_characters(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->mapo->map[i])
	{
		j = 0;
		while (data->mapo->map[i][j])
		{
			if (data->mapo->map[i][j])
			{
				if (ft_strchr("PENC01", data->mapo->map[i][j]) == 0)
					close_window(data, "invalid map character\n");
			}
			j++;
		}
		i++;
	}
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
			print_exit("bad map borders (vertically)\n", 1);
		i++;
	}
	i = 0;
	while (i < h)
	{
		if (map[i][0] != '1' || map[i][w - 1] != '1')
			print_exit("bad map borders (horizontally)\n", 1);
		i++;
	}
}

void	verify_map_name(int ac, char *av[])
{
	if (ac != 2)
		print_exit("bad args count\n", 1);
	if (ends_with(av[1], ".ber") == 0)
		print_exit("bad map name (should end with .ber)\n", 1);
}
