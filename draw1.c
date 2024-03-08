/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:41:26 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/06 20:18:14 by sgouzi           ###   ########.fr       */
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

void	put_p1l_img(t_data *data, int i, int j)
{
	t_assets	*images;

	images = data->imgs;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
		images->p1l_img, j * BOX_SIZE, i * BOX_SIZE);
}

void	put_p2l_img(t_data *data, int i, int j)
{
	t_assets	*images;

	images = data->imgs;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
		images->p2l_img, j * BOX_SIZE, i * BOX_SIZE);
}

void	put_p1r_img(t_data *data, int i, int j)
{
	t_assets	*images;

	images = data->imgs;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
		images->p1r_img, j * BOX_SIZE, i * BOX_SIZE);
}

void	put_p2r_img(t_data *data, int i, int j)
{
	t_assets	*images;

	images = data->imgs;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
		images->p2r_img, j * BOX_SIZE, i * BOX_SIZE);
}
