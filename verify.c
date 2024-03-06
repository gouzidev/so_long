/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:34:52 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/05 22:19:18 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	verify_map_width(t_data *data)
{
	int	i;
	int l;
	i = 1;

	l = len(data->mapo->map[0]);
	while (data->mapo->map[i])
	{
		if (len(data->mapo->map[i]) != l)
			close_window(data, "bad map width");
		i++;
	}
}


void	verify(t_data *data)
{
	t_map	*mapo;

	mapo = data->mapo;
	verify_borders(mapo);
	verify_map_width(data);
	verify_map_characters(data);
	verify_exit_count(data);
	verify_enemy_count(data);
	mapo->map_copy = copy_map(mapo->map, mapo->w, mapo->h);
	if (mapo->map_copy == NULL)
		close_window(data, "cant malloc map copy");
	flood(data);
}
