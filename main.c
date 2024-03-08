/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:34:32 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/06 20:57:03 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*malloc_or_print_exit(size_t size, char *msg)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		print_exit(msg, 1);
	return (ptr);
}

int	handle_input(int keysym, t_data *data)
{
	t_map	*mapo;

	mapo = data->mapo;
	if (keysym == 53)
		close_window_msg(data, "clicked on esc key");
	if (keysym == 13 || keysym == 126)
		move_up(data, mapo);
	if (keysym == 1 || keysym == 125)
		move_down(data, mapo);
	if (keysym == 2 || keysym == 124)
	{
		data->mapo->player->pd = 0;
		move_right(data, mapo);
	}
	if (keysym == 0 || keysym == 123)
	{
		data->mapo->player->pd = 1;
		move_left(data, mapo);
	}
	if (mapo->map[mapo->player->py][mapo->player->px] != 'E')
		mapo->map[mapo->player->py][mapo->player->px] = 'P';
	return (0);
}

void	init_null(t_data *data)
{
	data->mapo->player = NULL;
	data->mapo->map = NULL;
	data->mapo->enemy = NULL;
}

void	set_up(t_data *data, char *av[])
{
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
		print_exit("problem in mlx\n", 1);
	data->mapo = malloc_or_print_exit(sizeof(t_map), "problem in malloc\n");
	init_null(data);
	data->mapo->map = read_map(av[1]);
	data->mapo->enemy = malloc(sizeof(t_enemy));
	if (data->mapo->enemy == NULL)
		close_window_msg(data, "failed to malloc");
	data->mapo->player = malloc(sizeof(t_player));
	if (data->mapo->player == NULL)
		close_window_msg(data, "failed to malloc");
	set_mapo(data);
	data->mapo->player->p_frame = 0;
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->mapo->w * BOX_SIZE,
			data->mapo->h * BOX_SIZE, "sooooo long");
	if (data->mlx.win == NULL)
	{
		free_map(data->mapo->map);
		free(data->mapo);
		print_exit("problem in making th\n", 1);
	}
	data->mapo->player->count = 0;
	set_images(data);
	verify(data);
}

int	main(int ac, char *av[])
{
	t_data	data;

	verify_map_name(ac, av);
	set_up(&data, av);
	mlx_hook(data.mlx.win, 2, 0, handle_input, &data);
	mlx_loop_hook(data.mlx.mlx, draw, &data);
	mlx_hook(data.mlx.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx.mlx);
	close_window(&data);
}
