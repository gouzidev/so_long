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
typedef struct s_map
{
    char **map;
    int w;
    int h;
    int px;
    int py;
    int collectables_count;
}   t_map;

void verify_map(char **map, int w, int h)
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
void move_player(t_data *data, int m_h, int m_w, int direction)
{
  /*
    0 up
    1 down
    2 right
    3 left
*/
  char **map = data->map;
    t_player *p = data->player;
    if (direction == 0)
    {
        if (p->y - 1 > 0 && map[p->y - 1][p->x]  != '1')
        {
            map[p->y][p->x] = '0';
            if (map[p->y - 1][p->x] == 'E')
            {
                if (data->collectables_count == 0)
                    exit(1);
            }
            else
                p->y -= 1;
        }
    }
    else if (direction == 1)
    {
        if (p->y + 1 < m_h - 1 && map[p->y + 1][p->x] != '1')
        {
            map[p->y][p->x] = '0';
            if (map[p->y + 1][p->x] == 'E')
            {
                if (data->collectables_count == 0)
                    exit(1);
            }
            else
                p->y += 1;
        }
    }
    else if (direction == 2)
    {
        if (p->x + 1 < m_w - 1  && map[p->y][p->x + 1]  != '1')
        {
            map[p->y][p->x]  = '0';
            if (map[p->y][p->x + 1] == 'E')
            {
                if (data->collectables_count == 0)
                    exit(1);
            }
            else
                p->x += 1;
        }
    }
    else if (direction == 3)
    {
        if (p->x - 1 > 0 && map[p->y][p->x - 1] != '1')
        {
            map[p->y][p->x] = '0';
            if (map[p->y][p->x - 1] == 'E')
            {
                if (data->collectables_count == 0)
                    exit(1);
            }
            else
                p->x -= 1;
        }
    }
}
int handle_input(int keysym, t_data *data)
{   int map_h;
    int map_w;
    char **map = data->map;
    t_player *p = data->player;
    calculate_map_size(map, &map_w, &map_h, &data->collectables_count);
    if (keysym == XK_Up)
    {
        move_player(data, map_h, map_w, 0);
    }
    if (keysym == XK_Down)
    {
        move_player(data, map_h, map_w, 1);
    }
    if (keysym == XK_Right)
    {
        move_player(data, map_h, map_w, 2);

    }
    if (keysym == XK_Left)
    {
        move_player(data, map_h, map_w, 3);
        
    }

    if (map[p->y][p->x] != 'E')
        map[p->y][p->x] = 'P';
    print_map(data->map);
    return (0);
}
void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}
int draw_map(t_data *data)
{
    // 0 empty space,
    // 1 wall,
    // C collectible,
    // E map exit,
    // P player
    int img_w;
    int img_h;
    int map_h;
    int map_w;
    int i;
    int j;
    void *wall_img;
    void *floor_img;
    void *coin_img;
    void *exit_img;
    void *player_img;
    void *demon0_img;
    void *p1_img;
    void *mlx;
    void *win;
    t_img img;

    img = data->img;
    mlx = data->mlx.mlx;
    win = data->mlx.win;
    i = 0;
    j = 0;
    if (img.img == NULL)
    {
        printf("problem in img\n");
        exit(1);
    }
    
    wall_img = mlx_xpm_file_to_image(mlx, "./wall.xpm", &img_w, &img_h);
    floor_img = mlx_xpm_file_to_image(mlx, "./floor.xpm", &img_w, &img_h);
    exit_img = mlx_xpm_file_to_image(mlx, "./exit.xpm", &img_w, &img_h);
    p1_img = mlx_xpm_file_to_image(mlx, "./p1.xpm", &img_w, &img_h);
    coin_img = mlx_xpm_file_to_image(mlx, "./coin.xpm", &img_w, &img_h);
 
    if (calculate_map_size(data->map, &map_w, &map_h, &data->collectables_count) == 1)
    {

        printf("bad map \n");
        exit(1);
    }
    verify_map(data->map, map_w, map_h);

    mlx_destroy_image(data->mlx.mlx, data->img.img);
    data->img.img = mlx_new_image(data->mlx.mlx, 500, 500);
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length,
                                 &data->img.endian);
    while (i < map_h)
    {
        j = 0;
        while (j < map_w)
        {
            if (data->map[i][j] == '1')
                mlx_put_image_to_window(mlx, win, wall_img, j * 50, i * 50);
            else if (data->map[i][j] == '0')
                mlx_put_image_to_window(mlx, win, floor_img, j * 50, i * 50);
            else if (data->map[i][j] == 'P')
            {
                data->player->y = i;
                data->player->x = j;
                mlx_put_image_to_window(mlx, win, p1_img, j * 50, i * 50);
            }
            else if (data->map[i][j] == 'E')
                mlx_put_image_to_window(mlx, win, exit_img, j * 50, i * 50);
            else if (data->map[i][j] == 'C')
            {
                mlx_put_image_to_window(mlx, win, coin_img, j * 50, i * 50);
            }
            else
            {
                printf("bad map (invalid character) %c\n\n", data->map[i][j]);
                exit(1);
            }
            j++;
        }
        i++;
    }
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

/*

111111111
100000C01
1000E0C11
100P00001
111111111
*/


int main(int ac, char *av[])
{
    char **map;
    int fd;
    int line_count;
    char *line;
    int line_len;
    fd = open("map2.ber", O_RDONLY);
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
    fd = open("map2.ber", O_RDONLY);
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
    t_mlx mlx;
    t_img img;
    t_data data;
    t_player p;
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx,
                             WINDOW_WIDTH,
                             WINDOW_HEIGHT,
                             "My first window!");
    img.img = mlx_new_image(mlx.mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    data.img = img;
    data.mlx = mlx;
    data.player = &p;
    data.map = map;
    mlx_key_hook(mlx.win, handle_input, &data);
    
    mlx_loop_hook(mlx.mlx, draw_map, &data);

    mlx_loop(mlx.mlx);
}