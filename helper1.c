/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:54:41 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/06 20:53:04 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	set_images(t_data *data)
{
	int	img_w;
	int	img_h;

	data->imgs = malloc(sizeof(t_assets));
	data->imgs->wall_img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/wall.xpm", &img_w, &img_h);
	data->imgs->floor_img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/floor.xpm", &img_w, &img_h);
	data->imgs->exit_img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/exit.xpm", &img_w, &img_h);
	data->imgs->p1r_img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/p1r.xpm", &img_w, &img_h);
	data->imgs->p2r_img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/p2r.xpm", &img_w, &img_h);
	data->imgs->p1l_img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/p1l.xpm", &img_w, &img_h);
	data->imgs->p2l_img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/p2l.xpm", &img_w, &img_h);
	data->imgs->coin_img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/coin.xpm", &img_w, &img_h);
	data->imgs->demon_img = mlx_xpm_file_to_image(data->mlx.mlx,
			"./assets/demon0.xpm", &img_w, &img_h);
}

int	print_exit(char *msg, int exit_msg)
{
	ft_printf("%s", msg);
	exit(exit_msg);
}

void	close_window_msg(t_data *data, char *msg)
{
	t_map	*mapo;

	mapo = data->mapo;
	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	free_map(mapo->map);
	ft_free(mapo->enemy);
	ft_free(mapo->player);
	ft_printf("%s\n", msg);
	ft_free(mapo);
	exit(1);
}

int	close_window(t_data *data)
{
	t_map	*mapo;

	mapo = data->mapo;
	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	free_map(mapo->map);
	ft_free(mapo->enemy);
	ft_free(mapo->player);
	ft_free(mapo);
	exit(1);
	return (1);
}
