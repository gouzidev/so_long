/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:34:39 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/05 22:42:52 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	check_enemy(t_data *data, t_map *mapo, int next_y, int next_x)
{
	if (mapo->map[next_y][next_x] == 'N')
		close_window(data, "lost :\\");
}

void	move_up(t_data *data, t_map *mapo)
{
	if (mapo->py - 1 > 0 && mapo->map[mapo->py - 1][mapo->px] != '1')
	{
		ft_printf("%d\n", data->movement_counter);
		mapo->map[mapo->py][mapo->px] = '0';
		check_enemy(data, mapo, mapo->py - 1, mapo->px);
		if (mapo->map[mapo->py - 1][mapo->px] == 'C')
			mapo->cc--;
		if (mapo->map[mapo->py - 1][mapo->px] == 'E')
		{
			if (mapo->cc == 0)
				close_window(data, "won!");
		}
		else
		{
			data->movement_counter++;
			mapo->py -= 1;
		}
	}
}

void	move_down(t_data *data, t_map *mapo)
{
	if (mapo->py + 1 < mapo->h && mapo->map[mapo->py + 1][mapo->px] != '1')
	{
		ft_printf("%d\n", data->movement_counter);
		mapo->map[mapo->py][mapo->px] = '0';
		check_enemy(data, mapo, mapo->py + 1, mapo->px);
		if (mapo->map[mapo->py + 1][mapo->px] == 'C')
			mapo->cc--;
		if (mapo->map[mapo->py + 1][mapo->px] == 'E')
		{
			if (mapo->cc == 0)
				close_window(data, "won!");
		}
		else
		{
			data->movement_counter++;
			mapo->py += 1;
		}
	}
}

void	move_left(t_data *data, t_map *mapo)
{
	data->mapo->pd = 1;
	if (mapo->px - 1 > 0 && mapo->map[mapo->py][mapo->px - 1] != '1')
	{
		ft_printf("%d\n", data->movement_counter);
		mapo->map[mapo->py][mapo->px] = '0';
		check_enemy(data, mapo, mapo->py, mapo->px - 1);
		if (mapo->map[mapo->py][mapo->px - 1] == 'C')
			mapo->cc--;
		if (mapo->map[mapo->py][mapo->px - 1] == 'E')
		{
			if (mapo->cc == 0)
				close_window(data, "won!");
		}
		else
		{
			data->movement_counter++;
			mapo->px -= 1;
		}
	}
}

void	move_right(t_data *data, t_map *mapo)
{
	data->mapo->pd = 0;
	if (mapo->px + 1 < mapo->w && mapo->map[mapo->py][mapo->px + 1] != '1')
	{
		ft_printf("%d\n", data->movement_counter);
		mapo->map[mapo->py][mapo->px] = '0';
		check_enemy(data, mapo, mapo->py, mapo->px + 1);
		if (mapo->map[mapo->py][mapo->px + 1] == 'C')
			mapo->cc--;
		if (mapo->map[mapo->py][mapo->px + 1] == 'E')
		{
			if (mapo->cc == 0)
				close_window(data, "won!");
		}
		else
		{
			data->movement_counter++;
			mapo->px += 1;
		}
	}
}
