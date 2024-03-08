/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:40:19 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/06 20:46:31 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	move_enemy_down(t_data *data, t_map *mapo)
{
	int	ey;
	int	ex;

	ey = mapo->enemy->y;
	ex = mapo->enemy->x;
	if (ey + 1 < mapo->h - 1 && mapo->map[ey + 1][ex] != '1' && mapo->map[ey
		+ 1][ex] != 'C' && mapo->map[ey + 1][ex] != 'E')
	{
		mapo->map[ey][ex] = '0';
		if (mapo->map[ey + 1][ex] == 'P')
			close_window_msg(data, "lost!");
		else
			ey += 1;
	}
	else
		mapo->enemy->movement_direction = 1;
	mapo->enemy->y = ey;
	mapo->enemy->x = ex;
	mapo->map[ey][ex] = 'N';
}

void	move_enemy_up(t_data *data, t_map *mapo)
{
	int	ey;
	int	ex;

	ey = mapo->enemy->y;
	ex = mapo->enemy->x;
	if (ey - 1 >= 0 && mapo->map[ey - 1][ex] != '1' && mapo->map[ey
		- 1][ex] != 'C' && mapo->map[ey - 1][ex] != 'E')
	{
		mapo->map[ey][ex] = '0';
		if (mapo->map[ey - 1][ex] == 'P')
			close_window_msg(data, "lost!");
		else
			ey -= 1;
	}
	else
		mapo->enemy->movement_direction = 0;
	mapo->enemy->y = ey;
	mapo->enemy->x = ex;
	mapo->map[ey][ex] = 'N';
}

int	check_enemy_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->mapo->map[i])
	{
		j = 0;
		while (data->mapo->map[i][j])
		{
			if (data->mapo->map[i][j] == 'N')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	move_enemy(t_data *data)
{
	static int	i;
	int			h;

	if (check_enemy_map(data) == 0)
		return ;
	h = data->mapo->h;
	if (++i >= 6)
	{
		if (data->mapo->enemy->movement_direction == 1)
		{
			move_enemy_up(data, data->mapo);
			if (data->mapo->enemy->y < 1 || data->mapo->enemy->y - 1 == '1')
				data->mapo->enemy->movement_direction = 0;
		}
		else if (data->mapo->enemy->movement_direction == 0)
		{
			move_enemy_down(data, data->mapo);
			if (data->mapo->enemy->y >= h - 1 || data->mapo->enemy->y
				+ 1 == '1')
				data->mapo->enemy->movement_direction = 1;
		}
		i = 0;
	}
}
