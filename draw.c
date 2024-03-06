/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:33:45 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/05 21:24:43 by sgouzi           ###   ########.fr       */
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
