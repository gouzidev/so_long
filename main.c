/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:34:32 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/06 16:13:40 by sgouzi           ###   ########.fr       */
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
		close_window(data, "clicked on esc key");
	if (keysym == 13 || keysym == 126)
		move_up(data, mapo);
	if (keysym == 1 || keysym == 125)
		move_down(data, mapo);
	if (keysym == 2 || keysym == 124)
		move_right(data, mapo);
	if (keysym == 0 || keysym == 123)
		move_left(data, mapo);
	if (mapo->map[mapo->py][mapo->px] != 'E')
		mapo->map[mapo->py][mapo->px] = 'P';
	return (0);
}

void	set_up(t_data *data, char *av[])
{
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
		print_exit("problem in mlx\n", 1);
	data->mapo = malloc_or_print_exit(sizeof(t_map), "problem in malloc\n");
	data->mapo->map = read_map(av[1]);
	data->mapo->enemy = malloc(sizeof(t_enemy));
	if (data->mapo->enemy == NULL)
		close_window(data, "failed to malloc");
	set_mapo(data);
	data->mapo->p_frame = 0;
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->mapo->w * BOX_SIZE,
			data->mapo->h * BOX_SIZE, "sooooo long");
	if (data->mlx.win == NULL)
	{
		free_map(data->mapo->map);
		free(data->mapo);
		print_exit("problem in making th\n", 1);
	}
	data->movement_counter = 0;
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
	mlx_hook(data.mlx.win, 17, 0, close_smoothly, &data);
	mlx_loop(data.mlx.mlx);
	free_imgs_exit(data.imgs, 0);
	mlx_destroy_window(data.mlx.mlx, data.mlx.win);
}
