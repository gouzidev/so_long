/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 02:08:15 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/05 21:29:13 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	flood_e_path(int px, int py, t_map *mapo)
{
	char	**map;

	map = mapo->map_copy;
	if (px < 1 || px > mapo->w || py < 1 || py > mapo->h)
		return ;
	if (map[py][px] == 'V' || map[py][px] == '1' || map[py][px] == 'N')
		return ;
	if (map[py][px] == '0' || map[py][px] == 'C' || map[py][px] == 'E')
		map[py][px] = 'V';
	flood_e_path(px - 1, py, mapo);
	flood_e_path(px + 1, py, mapo);
	flood_e_path(px, py - 1, mapo);
	flood_e_path(px, py + 1, mapo);
}

void	check_e(t_map *mapo)
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
			if (map[i][j] == 'E')
			{
				ft_printf("no exit, bad map\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	flood_c_path(int px, int py, t_map *mapo)
{
	char	**map;

	map = mapo->map_copy;
	if (px < 1 || px >= mapo->w || py < 1 || py >= mapo->h)
		return ;
	if (map[py][px] == 'V' || map[py][px] == '1' || map[py][px] == 'E'
		|| map[py][px] == 'N')
		return ;
	if (map[py][px] == '0' || map[py][px] == 'C')
		map[py][px] = 'V';
	flood_c_path(px - 1, py, mapo);
	flood_c_path(px + 1, py, mapo);
	flood_c_path(px, py - 1, mapo);
	flood_c_path(px, py + 1, mapo);
}

void	check_c(t_map *mapo)
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
			if (map[i][j] == 'C')
			{
				ft_printf("bad map ( unreachable collectable(s) )\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}
