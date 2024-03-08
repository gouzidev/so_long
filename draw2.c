/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:41:27 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/06 20:49:14 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_count_str(t_data *data)
{
	char	*movement_count_str;
	char	*movement_msg;
	char	*count_word_str;

	movement_count_str = ft_itoa(data->mapo->player->count);
	if (movement_count_str == NULL)
		close_window_msg(data, "failed to malloc\n");
	count_word_str = ft_strdup("count ");
	if (count_word_str == NULL)
		close_window_msg(data, "failed to malloc\n");
	movement_msg = ft_strjoin(count_word_str, movement_count_str);
	if (movement_msg == NULL)
		close_window_msg(data, "failed to malloc\n");
	mlx_string_put(data->mlx.mlx, data->mlx.win, 20, 20, 0xFFFFFF,
		movement_msg);
	ft_free(movement_count_str);
	ft_free(count_word_str);
	ft_free(movement_msg);
}

void	put_coin_img(t_data *data, int i, int j)
{
	t_assets	*images;

	images = data->imgs;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, images->coin_img, j
		* BOX_SIZE, i * BOX_SIZE);
}

void	put_enemy_img(t_data *data, int i, int j)
{
	t_assets	*images;

	images = data->imgs;
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, images->demon_img, j
		* BOX_SIZE, i * BOX_SIZE);
}

void	handle_player(t_data *data, int i, int j, int *p_count)
{
	if (*p_count >= 80)
	{
		if (data->mapo->player->p_frame == 1)
			data->mapo->player->p_frame = 0;
		else
			data->mapo->player->p_frame = 1;
		*p_count = 0;
	}
	set_player(data->mapo, i, j);
	if (data->mapo->player->pd == 0)
	{
		if (data->mapo->player->p_frame == 0)
			put_p1r_img(data, i, j);
		else
			put_p2r_img(data, i, j);
	}
	else
	{
		if (data->mapo->player->p_frame == 0)
			put_p1l_img(data, i, j);
		else
			put_p2l_img(data, i, j);
	}
}

void	draw_map_images(t_map *mapo, t_data *data)
{
	static int	p_count;
	int			i;
	int			j;

	i = -1;
	while (p_count++ >= 0 && ++i < mapo->h)
	{
		j = -1;
		while (++j < mapo->w)
		{
			put_floor_img(data, i, j);
			if (mapo->map[i][j] == 'P')
				handle_player(data, i, j, &p_count);
			else if (mapo->map[i][j] == '0')
				put_floor_img(data, i, j);
			else if (mapo->map[i][j] == 'E')
				put_exit_img(data, i, j);
			else if (mapo->map[i][j] == 'C')
				put_coin_img(data, i, j);
			else if (mapo->map[i][j] == 'N')
				put_enemy_img(data, i, j);
			else if (mapo->map[i][j] == '1')
				put_wall_img(data, i, j);
		}
	}
}
