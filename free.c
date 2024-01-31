#include "header.h"

void ft_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
void free_map_exit(char **map, int should_exist)
{
	int i;

	i = 0;
	while (map[i])
	{
		printf("freeing   %s\n", map[i]);
		free(map[i]);
		i++;
	}
	free(map);
	if (should_exist == 1)
		exit(1);
}
void free_mapo_and_exit(t_map *mapo)
{
	free(mapo->map);
	free(mapo);
	exit(1);
}
void free_imgs_exit(t_assets *images, int should_exit)
{
	if (images->coin_img != NULL)
		free(images->coin_img);
	if (images->exit_img != NULL)
		free(images->exit_img);
	if (images->floor_img != NULL)
		free(images->floor_img);
	if (images->player_img != NULL)
		free(images->player_img);
	if (images->wall_img != NULL)
		free(images->wall_img);
	free(images);
	//	if (images->demon0_img != NULL)
	// free(images->demon0_img);
	if (should_exit)
		exit(1);
}
