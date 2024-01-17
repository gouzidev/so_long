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
int handle_input(int keysym, t_mlx *mlx)
{
    // Check the #defines
    // find / -name keysym.h 2>/dev/null
    // find / -name keysymdef.h 2>/dev/null
    if (keysym == XK_Escape)
    {
        printf("The %d key (ESC) has been pressed\n\n", keysym);
        mlx_destroy_window(mlx->mlx, mlx->win);
        mlx_destroy_display(mlx->mlx);
        free(mlx->mlx);
        exit(1);
    }
    printf("The %d key has been pressed\n\n", keysym);
    return (0);
}
typedef struct s_img
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_img;

typedef struct s_data
{
    t_img img;
    t_mlx mlx;
} t_data;

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
// 0 empty space,
// 1 wall,
// C collectible,
// E map exit,
// P player
int draw_map(t_mlx mlx)
{
    char *map1[] = {
    "1111111111111",
    "1C010T000T0C1",
    "1000011111001",
    "1P0011ET00001",
    "1111111111111"};

    int img_w;
    int img_h;
    int map_h;
    int map_w;
    int i;
    int j;
    void *wall_img;
    void *floor_img;

    i = 0;
    j = 0;
    wall_img = mlx_xpm_file_to_image(mlx.mlx, "./assets/world/map/wall.xpm", &img_w, &img_h);
    floor_img = mlx_xpm_file_to_image(mlx.mlx, "./assets/world/map/floor.xpm", &img_w, &img_h);
    map_w = strlen(map1[0]);
    map_h = sizeof(map1) / sizeof(map1[0]);
    while (i < map_h)
    {
        j = 0;
        while (j < map_w)
        {
            if (map1[i][j] == '1')
                mlx_put_image_to_window(mlx.mlx, mlx.win, wall_img, i * 50, j * 50);
            else
                mlx_put_image_to_window(mlx.mlx, mlx.win, floor_img, i * 50, j * 50);
            j++;
        }
        i++;
    }
        
    printf("width -> %d \n", img_w);
    printf("heigh -> %d \n", img_h);
}
int main(void)
{
    t_mlx mlx;
    t_img img;
    t_data data;

    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx,
                             WINDOW_WIDTH,
                             WINDOW_HEIGHT,
                             "My first window!");
    mlx_key_hook(mlx.win, handle_input, &mlx);
    img.img = mlx_new_image(mlx.mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    data.img = img;
    data.mlx = mlx;
    draw_map(mlx);

    mlx_loop(mlx.mlx);
}