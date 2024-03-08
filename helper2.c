/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:54:51 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/06 19:05:24 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	check_cell(t_map *mapo, int i, int j)
{
	if (mapo->map[i][j] == 'C')
		mapo->cc++;
	if (mapo->map[i][j] == 'P')
	{
		mapo->player->py = i;
		mapo->player->px = j;
	}
	if (mapo->map[i][j] == 'N')
	{
		mapo->enemy->y = i;
		mapo->enemy->x = j;
	}
}

void	set_mapo(t_data *data)
{
	int		i;
	int		j;
	t_map	*mapo;

	i = 0;
	mapo = data->mapo;
	mapo->enemy->movement_direction = 0;
	mapo->cc = 0;
	mapo->player->px = -1;
	mapo->player->py = -1;
	mapo->player->pd = 0;
	while (mapo->map[i])
	{
		j = 0;
		while (mapo->map[i][j])
		{
			check_cell(mapo, i, j);
			j++;
		}
		i++;
	}
	mapo->h = i;
	mapo->w = j;
}

void	set_up_data_struct(t_data *data, t_mlx mlx, t_map *mapo)
{
	data->mlx = mlx;
	data->mapo = mapo;
}

void	set_player(t_map *mapo, int i, int j)
{
	mapo->player->px = j;
	mapo->player->py = i;
}
