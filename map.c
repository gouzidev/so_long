#include "header.h"

char	**load_map(int fd, int line_count)
{
	int		line_len;
	char	**map;
	char	*line;

	map = malloc((line_count + 1) * sizeof(char *));
	if (map == NULL)
		print_exit("problem loading the map\n", 1);
	line = get_next_line(fd);
	line_count = 0;
	while (line)
	{
		line_len = ft_strlen_till(line, '\n');
		map[line_count] = ft_strdup_len_nonl(line, line_len);
		free(line);
		if (map[line_count] == NULL)
			free_map_exit(map, 1);
		line_count++;
		line = get_next_line(fd);
	}
	line_len = ft_strlen(line);
	map[line_count] = ft_strdup_len_nonl(line, line_len);
	free(line);
	return (map);
}
char	**read_map(char *path)
{
	char	**map;
	int		fd;
	int		line_count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
		print_exit("problem reading the file\n", 1);
	line = get_next_line(fd);
	line_count = 0;
	while (line)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	fd = open(path, O_RDONLY);
	if (fd <= 0)
		print_exit("problem reading the file\n", 1);
	map = load_map(fd, line_count);
	return (map);
}
char	**copy_map(char **map, int w, int h)
{
	char	**new_map;
	int		i;
	int		j;

	i = 0;
	new_map = malloc((h + 1) * sizeof(char *));
	if (new_map == NULL)
		return (NULL);
	while (map[i])
	{
		new_map[i] = ft_strdup_len_nonl(map[i], w);
		if (new_map[i] == NULL)
			free_map_exit(new_map, 0);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}