/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 02:08:18 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/06 20:46:31 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	flood_n_path(int px, int py, t_map *mapo)
{
	char	**map;

	map = mapo->map_copy;
	if (px < 1 || px > mapo->w || py < 1 || py > mapo->h)
		return ;
	if (map[py][px] == 'V' || map[py][px] == '1' || map[py][px] == 'E')
		return ;
	if (map[py][px] == '0' || map[py][px] == 'C' || map[py][px] == 'N')
		map[py][px] = 'V';
	flood_n_path(px - 1, py, mapo);
	flood_n_path(px + 1, py, mapo);
	flood_n_path(px, py - 1, mapo);
	flood_n_path(px, py + 1, mapo);
}

void	check_n(t_map *mapo)
{
	int		i;
	int		j;
	char	**map;

	map = mapo->map_copy;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N')
			{
				ft_printf("bad map ( unreachable ennemy )\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	flood(t_data *data)
{
	t_map	*mapo;

	mapo = data->mapo;
	flood_c_path(mapo->player->px, mapo->player->py, mapo);
	check_c(mapo);
	free_map(mapo->map_copy);
	mapo->map_copy = copy_map(mapo->map, mapo->w, mapo->h);
	if (mapo->map_copy == NULL)
		close_window_msg(data, "cant malloc map copy");
	flood_e_path(mapo->player->px, mapo->player->py, mapo);
	check_e(mapo);
	free_map(mapo->map_copy);
	mapo->map_copy = copy_map(mapo->map, mapo->w, mapo->h);
	if (mapo->map_copy == NULL)
		close_window_msg(data, "cant malloc map copy");
	if (check_enemy_map(data) == 1)
	{
		flood_n_path(mapo->player->px, mapo->player->py, mapo);
		check_n(mapo);
		free_map(mapo->map_copy);
	}
}
