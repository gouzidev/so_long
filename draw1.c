/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:41:26 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/05 17:48:29 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	put_wall_img(t_data *data, int i, int j)
{
	t_assets	*images;

	images = data->imgs;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, images->wall_img, j
		* BOX_SIZE, i * BOX_SIZE);
}

void	put_player_left_img(t_data *data, int i, int j)
{
	t_assets	*images;

	images = data->imgs;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
		images->player_left_img, j * BOX_SIZE, i * BOX_SIZE);
}

void	put_player_right_img(t_data *data, int i, int j)
{
	t_assets	*images;

	images = data->imgs;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
		images->player_right_img, j * BOX_SIZE, i * BOX_SIZE);
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
