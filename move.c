#include "header.h"



void move_up(t_data *data, t_map *mapo)
{
	if (mapo->py - 1 > 0 && mapo->map[mapo->py - 1][mapo->px] != '1')
	{
		mapo->map[mapo->py][mapo->px] = '0';
		if (mapo->map[mapo->py - 1][mapo->px] == 'C')
			mapo->cc--;
		if (mapo->map[mapo->py - 1][mapo->px] == 'E')
		{
			if (mapo->cc == 0)
				close_window(data, "won!");
		}
		else
			mapo->py -= 1;
	}
	}
void move_down(t_data *data, t_map *mapo)
{
	if (mapo->py + 1 < mapo->h && mapo->map[mapo->py + 1][mapo->px] != '1')
	{
		mapo->map[mapo->py][mapo->px] = '0';
		if (mapo->map[mapo->py + 1][mapo->px] == 'C')
			mapo->cc--;
		if (mapo->map[mapo->py + 1][mapo->px] == 'E')
		{
			if (mapo->cc == 0)
				close_window(data, "won!");
		}
		else
			mapo->py += 1;
	}
}
void move_left(t_data *data, t_map *mapo)
{
	if (mapo->px - 1 > 0 && mapo->map[mapo->py][mapo->px - 1] != '1')
	{
		mapo->map[mapo->py][mapo->px] = '0';
		if (mapo->map[mapo->py][mapo->px - 1] == 'C')
			mapo->cc--;
		if (mapo->map[mapo->py][mapo->px - 1] == 'E')
		{
			if (mapo->cc == 0)
				close_window(data, "won!");
		}
		else
			mapo->px -= 1;
	}
}
void move_right(t_data *data, t_map *mapo)
{
	if (mapo->px + 1 < mapo->w && mapo->map[mapo->py][mapo->px + 1] != '1')
	{
		mapo->map[mapo->py][mapo->px] = '0';
		if (mapo->map[mapo->py][mapo->px + 1] == 'C')
			mapo->cc--;
		if (mapo->map[mapo->py][mapo->px + 1] == 'E')
		{
			if (mapo->cc == 0)
				close_window(data, "won!");
		}
		else
			mapo->px += 1;
	}
}

