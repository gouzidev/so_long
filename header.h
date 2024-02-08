/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajordan- <ajordan-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 10:12:35 by ajordan-          #+#    #+#             */
/*   Updated: 2021/10/20 00:19:06 by ajordan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H


#include "header.h"
#include <stdlib.h>
#include <fcntl.h>
#include "./minilibx_copy/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "./minilibx_copy/mlx.h"
#include <X11/keysym.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

# ifndef WINDOW_WIDTH
# define WINDOW_WIDTH 1000
# endif

# ifndef WINDOW_HEIGHT
# define WINDOW_HEIGHT 1000
# endif

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;
typedef struct s_assets
{
	void		*wall_img;
	void		*floor_img;
	void		*coin_img;
	void		*exit_img;
	void		*demon0_img;
	void		*player_img;
}				t_assets;
typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;
typedef struct s_map
{
	char		**map;
	int			w;
	int			h;
	int			px;
	int			py;
	int			cc;
}				t_map;
typedef struct s_player
{
	int			x;
	int			y;
	int			score;
}				t_player;
typedef struct s_data
{
	t_img		img;
	t_mlx		mlx;
	t_player	*player;
	t_map		*mapo;
	t_assets	*imgs;
}				t_data;

char	*get_next_line(int fd);
int		we_have_a_problem(int fd, char **str);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *left_str, char *buff);
size_t	ft_strlen(char *s);
char	*ft_get_line(char *left_str);
char	*get_rest(char *left_str);
size_t	ft_strlen_till(char *s, char c);


void free_imgs_exit(t_assets *images, int should_exit);
void free_mapo_and_exit(t_map *mapo);
void free_map_exit(char **map, int should_exist);
void ft_free(void *ptr);

void	move_vertical(t_data *data, t_map *mapo, int direction);
void	move_horizontal(t_data *data, t_map *mapo, int direction);
void	move_player(t_data *data, t_map *mapo, int direction);


void	verify(t_data *data);
void	verify_borders(t_map *mapo);
int	verify_exit(char **map, int w, int h, int py, int px);


void set_images(t_data *data);
int	print_exit(char *msg, int exit_msg);
void	set_mapo(t_map *mapo);
void set_up_data_struct(t_data *data, t_img img, t_mlx mlx, t_map *mapo);
void	set_px_py(t_map *mapo, int i, int j);


int	ends_with(char *s, char *end);
void	verify_map_name(int ac, char *av[]);
int	ft_istrlen(const char *s);
int	ft_sub_strlen(char *s, char c);
char	*ft_strdup_len_nonl(const char *s1, int len);


char	**load_map(int fd, int line_count);
char	**read_map(char *path);
char	**copy_map(char **map, int w, int h);

void	print_map(t_map *mapo);
void	draw_map_images(t_map *mapo, t_data *data, t_assets *images);
int	draw_map(t_data *data);
void close_window(t_data *data);


int **make_cc_arr(char **map, int w, int h, int cc);
int verify_cc(char **map, int w, int h, int py, int px);

#endif