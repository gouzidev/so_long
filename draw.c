/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:33:45 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/06 20:18:31 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	draw(t_data *data)
{
	move_enemy(data);
	draw_map_images(data->mapo, data);
	draw_count_str(data);
	return (0);
}

void	put_floor_img(t_data *data, int i, int j)
{
	t_assets	*images;

	images = data->imgs;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, images->floor_img, j
		* BOX_SIZE, i * BOX_SIZE);
}

void	put_exit_img(t_data *data, int i, int j)
{
	t_assets	*images;

	images = data->imgs;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, images->exit_img, j
		* BOX_SIZE, i * BOX_SIZE);
}
