/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:34:39 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/06 20:46:31 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	check_enemy(t_data *data, t_map *mapo, int next_y, int next_x)
{
	if (mapo->map[next_y][next_x] == 'N')
		close_window_msg(data, "lost :\\");
}

void	move_up(t_data *data, t_map *mapo)
{
	int	px;
	int	py;

	px = mapo->player->px;
	py = mapo->player->py;
	if (py - 1 > 0 && mapo->map[py - 1][px] != '1')
	{
		ft_printf("%d\n", data->mapo->player->count);
		mapo->map[py][px] = '0';
		check_enemy(data, mapo, py - 1, px);
		if (mapo->map[py - 1][px] == 'C')
			mapo->cc--;
		if (mapo->map[py - 1][px] == 'E')
		{
			usleep(200000);
			if (mapo->cc == 0)
				close_window_msg(data, "won!");
		}
		else
		{
			data->mapo->player->count++;
			py -= 1;
		}
	}
	mapo->player->py = py;
}

void	move_down(t_data *data, t_map *mapo)
{
	int	px;
	int	py;

	px = mapo->player->px;
	py = mapo->player->py;
	if (py + 1 < mapo->h && mapo->map[py + 1][px] != '1')
	{
		ft_printf("%d\n", data->mapo->player->count);
		mapo->map[py][px] = '0';
		check_enemy(data, mapo, py + 1, px);
		if (mapo->map[py + 1][px] == 'C')
			mapo->cc--;
		if (mapo->map[py + 1][px] == 'E')
		{
			usleep(200000);
			if (mapo->cc == 0)
				close_window_msg(data, "won!");
		}
		else
		{
			data->mapo->player->count++;
			py += 1;
		}
	}
	mapo->player->py = py;
}

void	move_left(t_data *data, t_map *mapo)
{
	int	px;
	int	py;

	px = mapo->player->px;
	py = mapo->player->py;
	if (px - 1 > 0 && mapo->map[py][px - 1] != '1')
	{
		ft_printf("%d\n", data->mapo->player->count);
		mapo->map[py][px] = '0';
		check_enemy(data, mapo, py, px - 1);
		if (mapo->map[py][px - 1] == 'C')
			mapo->cc--;
		if (mapo->map[py][px - 1] == 'E')
		{
			usleep(200000);
			if (mapo->cc == 0)
				close_window_msg(data, "won!");
		}
		else
		{
			data->mapo->player->count++;
			px -= 1;
		}
	}
	mapo->player->px = px;
}

void	move_right(t_data *data, t_map *mapo)
{
	int	px;
	int	py;

	px = mapo->player->px;
	py = mapo->player->py;
	if (px + 1 < mapo->w && mapo->map[py][px + 1] != '1')
	{
		ft_printf("%d\n", data->mapo->player->count);
		mapo->map[py][px] = '0';
		check_enemy(data, mapo, py, px + 1);
		if (mapo->map[py][px + 1] == 'C')
			mapo->cc--;
		if (mapo->map[py][px + 1] == 'E')
		{
			usleep(200000);
			if (mapo->cc == 0)
				close_window_msg(data, "won!");
		}
		else
		{
			data->mapo->player->count++;
			px += 1;
		}
	}
	mapo->player->px = px;
}
