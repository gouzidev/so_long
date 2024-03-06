/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:34:12 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/05 21:02:52 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_free(map[i]);
		i++;
	}
	ft_free(map);
}

void	free_mapo_and_exit(t_map *mapo)
{
	ft_free(mapo->map);
	ft_free(mapo);
	exit(1);
}

void	free_imgs_exit(t_assets *images, int should_exit)
{
	ft_free(images);
	if (should_exit)
		exit(1);
}
