#include "minilibx/mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "./gnl/get_next_line.h"
#include <stdio.h>
#define MLX_ERROR 1
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

typedef struct s_mlx
{
    void *mlx;
    void *win;
} t_mlx;
int map_height = 5;
typedef struct s_img
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_img;
typedef struct s_player
{
    int x;
    int y;
    int score;
}  t_player;
typedef struct s_data
{
    t_img img;
    t_mlx mlx;
    t_player *player;
    char **map;
    int collectables_count;
} t_data;

void verify_borders(char **map, int w, int h)
{
    int i;

    i = 0;
    while (i < w)
    {
        if (map[0][i] != '1' || map[h - 1][i] != '1')
        {
            printf("bad map\n");
            exit(1);
        }
        i++;
    }
    i = 0;
    while (i < h)
    {
        if (map[i][0] != '1' || map[i][w - 1] != '1')
        {
            printf("bad map\n");
            exit(1);
        }
        i++;
    }
}
void print_map(char **map)
{
    int i = 0;
    int j = 0;
    while (map[0][i++])
        write(1, "*", 1);
    write(1,"\n", 1);
    i = 0;
    while (map[i] != NULL)
    {
        j = 0;
        while (j < ft_strlen(map[i]))
        {
            write(1, &map[i][j], 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
}
int ft_sub_strlen(char *s, char c)
{
	int i;

	i = 0;
	while (*s != c)
	{
		s++;
	}
	while (*s == c)
	{
		i++;
		s++;
	}
	return (i);
}
int calculate_map_size(char **map, int *w, int *h, int *collectables_count)
{
    int i;
    int j;

    i = 0;
    *collectables_count = 0;
    while (map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if (map[i][j] == 'C')
                (*collectables_count)++;
            j++;
        }
        i++;
    }
    *h = i;
    *w = j;
    if (*w <= 2 || *h <= 2)
        return (1);
    return (0);
}
char	*ft_strdup_len_nonl(const char *s1, int len)
{
	int		i;
	char	*buf;

    if (s1 == NULL)
        return (NULL);
	buf = malloc((len + 1) * sizeof(char));
	if (buf == 0)
		return (0);
	i = -1;
	while (++i < len)
		buf[i] = s1[i];
	buf[i] = '\0';
	return (buf);
}
char **copy_map(char **map, int w, int h)
{
    char **new_map;
    int i;
    int j;

    i = 0;
    new_map = malloc((h + 1) * sizeof(char *));
    while (map[i])
    {
        new_map[i] = ft_strdup_len_nonl(map[i], w);
        i++;
    }
    new_map[i] = NULL;
    return (new_map);
}
int verify_exit(char **map, int w, int h, int py, int px)
{
    int r = 1;
    if (map[py][px] == 'E')
        return 0;
    if (map[py][px] == 'x')
        return 1;
    if (py - 1 >= 1 && map[py - 1][px] != '1' && map[py - 1][px] != 'x')
    {
        map[py][px] = 'x';
        r = verify_exit(map, w, h, py - 1, px);
        if (r == 0)
            return r;
    }
    if (px + 1 < w - 1 && map[py][px + 1] != '1' && map[py][px + 1] != 'x')
    {
        map[py][px] = 'x';
        r = verify_exit(map, w, h, py, px + 1);
        if (r == 0)
            return r;
    }
    if (px - 1 >= 1 && map[py][px - 1] != '1' && map[py][px - 1] != 'x')
    {
        map[py][px] = 'x';
        r = verify_exit(map, w, h, py, px - 1);
        if (r == 0)
            return r;
    }
    if (py + 1 < h - 1 && map[py + 1][px] != '1' && map[py + 1][px] != 'x')
    {
        map[py][px] = 'x';
        r = verify_exit(map, w, h, py + 1, px);
        if (r == 0)
            return r;
    }
    return r;
}

int main(int ac, char *av[])
{
    char **map;
    int fd;
    int line_count;
    char *line;
    int line_len;
    int w;
    int h;
    int cc;
    fd = open("map.ber", O_RDONLY);
    if (fd <= 0)
    {
        printf("problem reading the file\n");
        exit(1);
    }
    line = get_next_line(fd);
    line_count = 0;
    while (line)
    {
        line_count++;
        line = get_next_line(fd);
    }
    close(fd);
    fd = open("map.ber", O_RDONLY);
    if (fd <= 0)
    {
        printf("problem reading the file\n");
        exit(1);
    }
    map = malloc((line_count + 1) * sizeof(char *));
    line = get_next_line(fd);
    line_count = 0;
    while (line)
    {
        line_len = ft_strlen_till(line, '\n');
        map[line_count] = ft_strdup_len_nonl(line, line_len);
        line_count++;
        line = get_next_line(fd);
    }
    line_len = ft_strlen(line);
    map[line_count] = ft_strdup_len_nonl(line, line_len);
    calculate_map_size(map, &w, &h, &cc);
    char **copy = copy_map(map, w, h);
    print_map(map);
    printf("%d \n", verify_exit(copy, w, h, 3, 1));
}