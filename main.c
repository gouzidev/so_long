#include "minilibx/mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MLX_ERROR 1
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

/*
 * MLX_STRUCT
 * I stock all the mlx into a struct
 * because the handler function takes
 * (void *)pointer_to_mlx
 * I need therefore this gimmick to
 * pass more elements in one-go
 */
typedef struct s_mlx
{
    void *mlx;
    void *win;
} t_mlx;

/*
 * HANDLER FUNCTION
 * Every time a key is pressed this function is called
 *
 * KEYSYM vs KEYCODE
 * A keycode is a hardware-specific code sent by the keyboard  key press,
 * while a keysym is its abstract representation,
 * often used in software to identify the key regardless of hardware.
 * 🚨 MinilibX mac uses keycodes 🚨
 */
char *map[] = {
"1111111111111",
"1C010000000C1",
"1000011111001",
"1P0011E000001",
"1111111111111"
};
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
    char *map[];
} t_data;



int handle_input(int keysym, t_data *data)
{   int map_h;
    int map_w;
    map_w = strlen(map[0]);
    map_h = sizeof(map) / sizeof(data);
    // Check the #defines
    // find / -name keysym.h 2>/dev/null
    // find / -name keysymdef.h 2>/dev/null
    if (keysym == XK_Escape)
    {
        printf("The %d key (ESC) has been pressed\n\n", keysym);
        mlx_destroy_window(data->mlx.mlx, data->mlx.mlx);
        mlx_destroy_display(data->mlx.mlx);
        free(data->mlx.mlx);
        exit(1);
    }
    if (keysym == XK_Up)
    {
        if (data->player->y - 1 > 0 && data->player->y - 1 != '1')
        {
            data->player->y -= 1;
        }
    }
    if (keysym == XK_Down)
    {
        if (data->player->y + 1 < map_h && data->player->y + 1 != '1')
        {
            data->player->y += 1;
        }
        
    }
    if (keysym == XK_Right)
    {
        if (data->player->x + 1 < map_w && data->player->x + 1 != '1')
        {
            data->player->x += 1;
        }
    }
    if (keysym == XK_Left)
    {
        if (data->player->x + 1 > 0 && data->player->x + 1 != '1')
        {
            data->player->x -= 1;
        }
    }
    return (0);
}
void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int draw_square(t_img *img, int s)
{
    int i = 0;
    int j = 0;
    while (i < 100)
    {
        j = 0;
        while (j < 100)
        {
            my_mlx_pixel_put(img, i  + (s * 100), j, 429496729.5 * s);
            j++;
        }
        i++;
    }
}
int draw_squares(t_data *data)
{
    void *mlx = data->mlx.mlx;
    void *win = data->mlx.win;
    void *img = data->img.img;

    int i = 0;
    // win => 1000
    while (i < 10)
    {
        draw_square(&data->img, i);  
        i++;
    }

    mlx_put_image_to_window(mlx, win, img, 0, 0);


    return 0;
}
int verify_move()
{
    return (1);
}

// 0 empty space,
// 1 wall,
// C collectible,
// E map exit,
// P player
int draw_map(t_data *data)
{
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
    wall_img = mlx_xpm_file_to_image(mlx, "./wall.xpm", &img_w, &img_h);
    floor_img = mlx_xpm_file_to_image(mlx, "./floor.xpm", &img_w, &img_h);
    exit_img = mlx_xpm_file_to_image(mlx, "./exit.xpm", &img_w, &img_h);
    p1_img = mlx_xpm_file_to_image(mlx, "./p1.xpm", &img_w, &img_h);
    coin_img = mlx_xpm_file_to_image(mlx, "./coin.xpm", &img_w, &img_h);
    map_w = strlen(map[0]);
    map_h = sizeof(map) / sizeof(map[0]);
    while (i < map_h)
    {
        j = 0;
        while (j < map_w)
        {
            if (map[i][j] == '1')
                mlx_put_image_to_window(mlx, win, wall_img, j * 50, i * 50);
            else if (map[i][j] == '0')
                mlx_put_image_to_window(mlx, win, floor_img, j * 50, i * 50);
            else if (map[i][j] == 'P')
            {
                mlx_put_image_to_window(mlx, win, floor_img, j * 50, i * 50);
                mlx_put_image_to_window(mlx, win, p1_img, j * 50, i * 50);
            }
            else if (map[i][j] == 'E')
                mlx_put_image_to_window(mlx, win, exit_img, j * 50, i * 50);
            else if (map[i][j] == 'C')
            {
                mlx_put_image_to_window(mlx, win, floor_img, j * 50, i * 50);
                mlx_put_image_to_window(mlx, win, coin_img, j * 50, i * 50);
            }
            else
            {
                printf("bad map \n");
                exit(1);
            }
            j++;
        }
        i++;
    }
    printf("p x -> %d \n", data->player->x);
    printf("p y -> %d \n", data->player->y);
}


int main(void)
{
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
    mlx_key_hook(mlx.win, handle_input, &data);
    
    mlx_loop_hook(mlx.mlx, draw_map, &data);

    mlx_loop(mlx.mlx);
}