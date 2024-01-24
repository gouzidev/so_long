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
typedef struct s_img
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_img;
typedef struct s_map
{
    char **map;
    int w;
    int h;
    int px;
    int py;
    int cc;
}   t_map;

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
    t_map *mapo;
    int cc;
} t_data;
void print_map(t_map mapo)
{
    int i = 0;
    int j = 0;
    char **map;

    map = mapo.map;
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
void verify_map(t_map mapo)
{
    int i;

    i = 0;
    char **map;

    map = mapo.map;
    int w;
    int h;

    w = mapo.w;
    h = mapo.h;
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
int calculate_map_size(t_map *mapo)
{
    int i;
    int j;
    i = 0;
    char **map = mapo->map;

    while (map[i])
    {
        j = 0;

        while(map[i][j])
        {

            if (map[i][j] == 'C')
                mapo->cc++;

            if (map[i][j] == 'P')
            {
                mapo->py = i;
                mapo->px = j;
            }
            j++;
        }
        i++;
    }

    mapo->h = i;
    mapo->w = j;
    printf("h -> %d   w -> %d\n", mapo->h, mapo->w);

    if (mapo->w <= 2 || mapo->h <= 2)
        return (1);
    return (0);
}
void move_player(t_data *data, int m_h, int m_w, int direction, t_map *mapo)
{
  /*
    0 up
    1 down
    2 right
    3 left
*/
    char **map = mapo->map;
    t_player *p;
    p->x = mapo->px;
    p->y = mapo->py;

    if (direction == 0)
    {
        if (p->y - 1 > 0 && map[p->y - 1][p->x]  != '1')
        {
            map[p->y][p->x] = '0';
            if (map[p->y - 1][p->x] == 'E')
            {
                if (mapo->cc == 0)
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
                if (mapo->cc == 0)
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
                if (mapo->cc == 0)
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
                if (mapo->cc == 0)
                    exit(1);
            }
            else
                p->x -= 1;
        }
    }
}
int handle_input(int keysym, t_data *data)
{
    t_player *p;
    t_map *mapo;
    mapo = data->mapo;
    // mapo->map = copy_map(data->map/);
    p->x = data->player->x;
    p->y = data->player->y;

    // printf("x -> %d  y -> %d\n", p->x, p->y);
    // printf("w -> %d  h -> %d\n", mapo->w, mapo->h);


    printf("hello -> %d\n", calculate_map_size(data->mapo));

    if (keysym == XK_Up)
    {
        move_player(data, mapo->h, mapo->w, 0, mapo);
    }
    if (keysym == XK_Down)
    {
        move_player(data, mapo->h, mapo->w, 1, mapo);
    }
    if (keysym == XK_Right)
    {
        move_player(data, mapo->h, mapo->w, 2, mapo);
    }
    if (keysym == XK_Left)
    {
        move_player(data, mapo->h, mapo->w, 3, mapo);
        
    }

    if (mapo->map[p->y][p->x] != 'E')
        mapo->map[p->y][p->x] = 'P';
    printf("x -> %d  y -> %d\n",p->x,p->y);

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
    int img_w;
    int img_h;
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
    t_map *mapo;

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
    mapo = data->mapo;
    if (calculate_map_size(mapo) == 1)
    {
        printf("bad map \n");
        exit(1);
    }
    printf(",,,,,,,,\n");    
    verify_map(*mapo);

    mlx_destroy_image(data->mlx.mlx, data->img.img);
    data->img.img = mlx_new_image(data->mlx.mlx, 500, 500);
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length,
                                 &data->img.endian);
    while (i < mapo->h)
    {
        j = 0;
        while (j < mapo->w)
        {
            if (mapo->map[i][j] == '1')
                mlx_put_image_to_window(mlx, win, wall_img, j * 50, i * 50);
            else if (mapo->map[i][j] == '0')
                mlx_put_image_to_window(mlx, win, floor_img, j * 50, i * 50);
            else if (mapo->map[i][j] == 'P')
            {
                data->player->y = i;
                data->player->x = j;
                mapo->px = j;
                mapo->py = i;
                mlx_put_image_to_window(mlx, win, p1_img, j * 50, i * 50);
            }
            else if (mapo->map[i][j] == 'E')
                mlx_put_image_to_window(mlx, win, exit_img, j * 50, i * 50);
            else if (mapo->map[i][j] == 'C')
            {
                mlx_put_image_to_window(mlx, win, coin_img, j * 50, i * 50);
            }
            else
            {
                printf("bad map (invalid character) %c\n\n", mapo->map[i][j]);
                exit(1);
            }
            j++;
        }
        i++;
    }
}

int main(int ac, char *av[])
{
    t_map *mapo;
    char **map;
    int fd;
    int line_count;
    char *line;
    int line_len;
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
    data.player = malloc(sizeof(t_player));
    data.player = &p;
    data.map = map;
    mapo = malloc(sizeof(t_map));
    mapo->map = map;
    data.mapo = mapo;
    mlx_key_hook(mlx.win, handle_input, &data);
    
    mlx_loop_hook(mlx.mlx, draw_map, &data);

    mlx_loop(mlx.mlx);
}