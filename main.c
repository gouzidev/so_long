#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "./gnl_copy/get_next_line.h"
#define MLX_ERROR 1
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

typedef struct s_mlx
{
    void *mlx;
    void *win;
} t_mlx;
typedef struct s_assets {
    void *wall_img;
    void *floor_img;
    void *coin_img;
    void *exit_img;
    void *player_img;
    void *demon0_img;
    void *p1_img;
}  t_assets;
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
    t_map *mapo;
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
int	ft_istrlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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
int set_mapo(t_map *mapo)
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

    if (mapo->w <= 2 || mapo->h <= 2)
        return (1);
    return (0);
}
void verify_borders(t_map *mapo)
{
    int i;
    int w;
    int h;
    char **map;

    i = 0;
    map = mapo->map;
    w = mapo->w;
    h = mapo->h;
    while (i < w)
    {
        if (map[0][i] != '1' || map[h - 1][i] != '1')
        {
            printf("bad map borders\n");
            exit(1);
        }
        i++;
    }
    i = 0;
    while (i < h)
    {
        if (map[i][0] != '1' || map[i][w - 1] != '1')
        {
            printf("bad map borders\n");
            exit(1);
        }
        i++;
    }
}
int verify_exit(char **map, int w, int h, int py, int px)
{
    int r = 1;
    if (map[py][px] == 'E')
        return 0;
    if (map[py][px] == 'x')
        return 1;
    map[py][px] = 'x';
    if (py - 1 >= 1 && map[py - 1][px] != '1' && map[py - 1][px] != 'x')
    {
        r = verify_exit(map, w, h, py - 1, px);
        if (r == 0)
            return r;
    }
    if (px + 1 < w - 1 && map[py][px + 1] != '1' && map[py][px + 1] != 'x')
    {
        r = verify_exit(map, w, h, py, px + 1);
        if (r == 0)
            return r;
    }
    if (px - 1 >= 1 && map[py][px - 1] != '1' && map[py][px - 1] != 'x')
    {
        r = verify_exit(map, w, h, py, px - 1);
        if (r == 0)
            return r;
    }
    if (py + 1 < h - 1 && map[py + 1][px] != '1' && map[py + 1][px] != 'x')
    {
        r = verify_exit(map, w, h, py + 1, px);
        if (r == 0)
            return r;
    }
    return r;
}
void move_vertical(t_map *mapo, int direction)
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
                   exit(1);
            }
            else
                mapo->py -= 1;
        }
    }
    else if (direction == 2) // down
    {
        printf("px -> %d  py -> %d\n", mapo->px, mapo->py);
    printf("w -> %d  h -> %d\n", mapo->w, mapo->h);
        if (mapo->py + 1 < mapo->h && mapo->map[mapo->py + 1][mapo->px] != '1')
        {
            mapo->map[mapo->py][mapo->px] = '0';
            if (mapo->map[mapo->py + 1][mapo->px] == 'C')
                mapo->cc--;
            if (mapo->map[mapo->py + 1][mapo->px] == 'E')
            {
                if (mapo->cc == 0)
                   exit(1);
            }
            else
                mapo->py += 1;
        }
    }
}
void move_horizontal(t_map *mapo, int direction)
{
    if (direction == 1) // right
    {
        if (mapo->px + 1 < mapo->w && mapo->map[mapo->py][mapo->px + 1]  != '1')
        {
            mapo->map[mapo->py][mapo->px]  = '0';
            if (mapo->map[mapo->py][mapo->px + 1] == 'C')
                mapo->cc--;
            if (mapo->map[mapo->py][mapo->px + 1] == 'E')
            {
                if (mapo->cc == 0)
                   exit(1);
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
                   exit(1);
            }
            else
                mapo->px -= 1;
        }
    }
}
void move_player(t_map *mapo, int direction)
{
    int m_h = mapo->h;
    int m_w = mapo->w;
    if (direction % 2 == 0)
        move_vertical(mapo, direction);
    else
        move_horizontal(mapo, direction);

    mapo->map[mapo->py][mapo->px] = 'P';
    print_map(*mapo);
}
int handle_input(int keysym, t_data *data)
{
    t_map *mapo;
    mapo = data->mapo;

    // printf("px -> %d  py -> %d\n", mapo->px, mapo->py);
    // printf("w -> %d  h -> %d\n", mapo->w, mapo->h);

    set_mapo(data->mapo);
    if (keysym == 53)
        mlx_destroy_window(data->mlx.mlx, data->mlx.win);
    if (keysym == 13) // w
        move_player(mapo, 0);
    if (keysym == 1) // s
        move_player(mapo, 2);
    if (keysym == 2) //d
        move_player(mapo, 1);
    if (keysym == 0) // a
        move_player(mapo, 3);
    if (mapo->map[mapo->py][mapo->px] != 'E')
        mapo->map[mapo->py][mapo->px] = 'P';
    return (0);
}
void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}
int print_exit(char *msg, int exit_msg)
{
    printf("%s", msg);
    exit(exit_msg);
}
t_assets *set_images(t_data *data)
{
    int img_w;
    int img_h;
    t_assets *images;

    images = malloc(sizeof(t_assets));
    images->wall_img = mlx_xpm_file_to_image(data->mlx.mlx, "./wall.xpm", &img_w, &img_h);
    images->floor_img = mlx_xpm_file_to_image(data->mlx.mlx, "./floor.xpm", &img_w, &img_h);
    images->exit_img = mlx_xpm_file_to_image(data->mlx.mlx, "./exit.xpm", &img_w, &img_h);
    images->p1_img = mlx_xpm_file_to_image(data->mlx.mlx, "./p1.xpm", &img_w, &img_h);
    images->coin_img = mlx_xpm_file_to_image(data->mlx.mlx, "./coin.xpm", &img_w, &img_h);
    return (images);
}
void draw_map_images(t_map *mapo, t_data *data, t_assets *images)
{
    int i;
    int j;

    i = 0;
    while (i < mapo->h)
    {
        j = 0;
        while (j < mapo->w)
        {
            if (mapo->map[i][j] == '1')
                mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, images->wall_img, j * 50, i * 50);
            else if (mapo->map[i][j] == '0')
                mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, images->floor_img, j * 50, i * 50);
            else if (mapo->map[i][j] == 'P')
            {
                mapo->px = j;
                mapo->py = i;
                mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, images->p1_img, j * 50, i * 50);
            }
            else if (mapo->map[i][j] == 'E')
                mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, images->exit_img, j * 50, i * 50);
            else if (mapo->map[i][j] == 'C')
                mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, images->coin_img, j * 50, i * 50);
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
int draw_map(t_data *data)
{
    void *mlx;
    void *win;
    t_img img;
    t_map *mapo;
    t_assets *images;

    img = data->img;
    mlx = data->mlx.mlx;
    win = data->mlx.win;
    if (img.img == NULL)
        print_exit("problem in img\n", 1);
    images = set_images(data);

    mapo = data->mapo;
    mapo->cc = 0;
    if (set_mapo(mapo) == 1)
        print_exit("bad map\n", 1);
    verify_borders(mapo);
    data->img.img = mlx_new_image(data->mlx.mlx, 500, 500);
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length,
                                 &data->img.endian);
    draw_map_images(mapo, data, images);
    return (0);
}

char **load_map(int fd, int line_count)
{
    int line_len;
    char **map;
    char *line;

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
    return map;
}
char **read_map(char *path)
{
    char **map;
    int fd;
    int line_count;
    char *line;
    fd = open(path, O_RDONLY);
    if (fd <= 0)
        print_exit("problem reading the file\n", 1);
    line = get_next_line(fd);
    line_count = 0;
    while (line)
    {
        line_count++;
        line = get_next_line(fd);
    }
    close(fd);
    fd = open(path, O_RDONLY);
    if (fd <= 0)
        print_exit("problem reading the file\n", 1);
    map = load_map(fd, line_count);
    return map;
}
int ends_with(char *s, char *end)
{
    int i;
    int j;

    i = 0;
    int good;

    good = 0;
    while (s[i])
    {
        j = 0;
        while (s[i] == end[j])
        {
            i++;
            j++;
        if (s[i] == '\0')
            return (1);
        }
        i++;
    }
    return (0);
}
void verify_map_name(int ac,  char *av[])
{
    if (ac != 2)
        print_exit("bad args count\n", 1);
    if (ends_with(av[1], ".ber") == 0)
        print_exit("bad map name\n", 1);
}
int main(int ac, char *av[]) 
{
    // choof tv get images from there 
    t_map *mapo;
    t_mlx mlx;
    t_img img;
    t_data data;
    int r;

    char **map;
    char **map_copy;
    verify_map_name(ac, av);
    map = read_map(av[1]);
    mapo = malloc(sizeof(t_map));
    mapo->map = map;
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
    data.mapo = mapo;
    if (set_mapo(mapo) == 1)
        print_exit("bad map\n", 1);
    verify_borders(mapo);
    map_copy = copy_map(mapo->map, mapo->w, mapo->h);
    r = verify_exit(map_copy, mapo->w, mapo->h, mapo->py, mapo->px);
    if (r == 1)
        print_exit("shitty ass map\n", 1);
    mlx_key_hook(mlx.win, handle_input, &data);
    mlx_loop_hook(mlx.mlx, draw_map, &data);
    mlx_loop(mlx.mlx);
}