#include "header.h"

void	move_vertical(t_data *data, t_map *mapo, int direction)
{
	if (direction == 0) // up
	{
		if (mapo->py - 1 > 0 && mapo->map[mapo->py - 1][mapo->px] != '1')
		{
			mapo->map[mapo->py][mapo->px] = '0';
			if (mapo->map[mapo->py - 1][mapo->px] == 'C')
				mapo->cc--;
			if (mapo->map[mapo->py - 1][mapo->px] == 'E')
			{
				if (mapo->cc == 0)
					close_window(data);
			}
			else
				mapo->py -= 1;
		}
	}
	else if (direction == 2) // down
	{
		if (mapo->py + 1 < mapo->h && mapo->map[mapo->py + 1][mapo->px] != '1')
		{
			mapo->map[mapo->py][mapo->px] = '0';
			if (mapo->map[mapo->py + 1][mapo->px] == 'C')
				mapo->cc--;
			if (mapo->map[mapo->py + 1][mapo->px] == 'E')
			{
				if (mapo->cc == 0)
					close_window(data);
			}
			else
				mapo->py += 1;
		}
	}
}
void	move_horizontal(t_data *data, t_map *mapo, int direction)
{
	if (direction == 1) // right
	{
		if (mapo->px + 1 < mapo->w && mapo->map[mapo->py][mapo->px + 1] != '1')
		{
			mapo->map[mapo->py][mapo->px] = '0';
			if (mapo->map[mapo->py][mapo->px + 1] == 'C')
				mapo->cc--;
			if (mapo->map[mapo->py][mapo->px + 1] == 'E')
			{
				if (mapo->cc == 0)
					close_window(data);
			}
			else
				mapo->px += 1;
		}
	}
	else if (direction == 3) // left
	{
		if (mapo->px - 1 > 0 && mapo->map[mapo->py][mapo->px - 1] != '1')
		{
			mapo->map[mapo->py][mapo->px] = '0';
			if (mapo->map[mapo->py][mapo->px - 1] == 'C')
				mapo->cc--;
			if (mapo->map[mapo->py][mapo->px - 1] == 'E')
			{
				if (mapo->cc == 0)
					close_window(data);
			}
			else
				mapo->px -= 1;
		}
	}
}
void	move_player(t_data *data, t_map *mapo, int direction)
{
	int	m_h;
	int	m_w;

	m_h = mapo->h;
	m_w = mapo->w;
	if (direction % 2 == 0)
		move_vertical(data, mapo, direction);
	else
		move_horizontal(data, mapo, direction);
	mapo->map[mapo->py][mapo->px] = 'P';
}
