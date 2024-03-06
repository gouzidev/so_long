/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:42:58 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/05 22:31:41 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:34:22 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/05 12:48:09 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include <mlx.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1337
# endif

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 1000
# endif

# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 1000
# endif

# ifndef BOX_SIZE
#  define BOX_SIZE 50
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
	void		*demon_img;
	void		*player_right_img;
	void		*player_left_img;
}				t_assets;

typedef struct s_enemy
{
	int			x;
	int			y;
	int			is_killed;
	int			movement_direction;
}				t_enemy;

typedef struct s_player
{
	int			x;
	int			y;
	int			score;
	int			frame;
}				t_player;

typedef struct s_map
{
	char		**map;
	char		**map_copy;
	int			w;
	int			h;
	int			px;
	int			py;
	int			pd;
	int			cc;
	int			p_frame;
	t_enemy		*enemy;
}				t_map;

typedef struct s_data
{
	t_mlx		mlx;
	t_player	*player;
	t_map		*mapo;
	t_assets	*imgs;
	int			movement_counter;
}				t_data;

int				check_enemy_map(t_data *data);
void			move_enemy_down(t_data *data, t_map *mapo);
void			move_enemy_up(t_data *data, t_map *mapo);
void			move_enemy(t_data *data);

int				draw(t_data *data);
void			draw_map_images(t_map *mapo, t_data *data);

void			draw_count_str(t_data *data);
void			put_coin_img(t_data *data, int i, int j);
void			put_enemy_img(t_data *data, int i, int j);
void			handle_player(t_data *data, int i, int j, int *p_count);
void			put_wall_img(t_data *data, int i, int j);
void			put_player_left_img(t_data *data, int i, int j);
void			put_player_right_img(t_data *data, int i, int j);
void			put_floor_img(t_data *data, int i, int j);
void			put_exit_img(t_data *data, int i, int j);

void			flood_c_path(int px, int py, t_map *mapo);
void			check_c(t_map *mapo);
void			flood_e_path(int px, int py, t_map *mapo);
void			check_e(t_map *mapo);
void			flood_n_path(int px, int py, t_map *mapo);
void			check_n(t_map *mapo);
void			flood(t_data *data);

void			free_imgs_exit(t_assets *images, int should_exit);
void			free_mapo_and_exit(t_map *mapo);
void			ft_free(void *ptr);
void			free_map(char **map);

int				len(char *s);
void			ft_print_rec(unsigned long n, char *base, int *i);
void			ft_putint(int n, int *i);
void			ft_putunsigned(unsigned int n, int *i);
void			ft_putchar(char c, int *i);
void			ft_putstr(char *s, int *i);
void			ft_putaddr(void *p, int *i);
void			ft_puthex(unsigned int n, char x, int *i);
int				c_in_str(char c, char *s);
void			handler(va_list v, int *i, const char **s);
int				ft_printf(const char *s, ...);

void			set_images(t_data *data);

int				print_exit(char *msg, int exit_msg);
int				close_smoothly(t_data *data);
void			close_window(t_data *data, char *msg);
void			check_cell(t_map *mapo, int i, int j);
void			set_mapo(t_data *data);
void			set_up_data_struct(t_data *data, t_mlx mlx,
					t_map *mapo);
void			set_player(t_map *mapo, int i, int j);

int				count_digits(int n);
void			fill_rec(int n, char *buff, int *i);
int				ft_handle(int i, char *buff, int n);
char			*ft_itoa(int n);

void			set_up(t_data *data, char *av[]);
int				handle_input(int keysym, t_data *data);
void			*malloc_or_print_exit(size_t size, char *msg);
int				main(int ac, char *av[]);

char			**load_map(int fd, int line_count);
char			**read_map(char *path);
char			**copy_map(char **map, int w, int h);

void			move_up(t_data *data, t_map *mapo);
void			move_down(t_data *data, t_map *mapo);
void			move_left(t_data *data, t_map *mapo);
void			move_right(t_data *data, t_map *mapo);
void			check_enemy(t_data *data, t_map *mapo, int next_y, int next_x);

char			*get_next_line(int fd);
int				we_have_a_problem(int fd, char **str);
char			*ft_strchr(char *s, int c);
char			*ft_gnl_strjoin(char *left_str, char *buff);
char			*ft_strjoin(char *s1, char *s2);
size_t			ft_strlen(char *s);
char			*ft_get_line(char *left_str);
char			*get_rest(char *left_str);
size_t			ft_strlen_till(char *s, char c);
char			*ft_strdup(const char *s1);
int				ft_strcmp(const char *s1, const char *s2);
int				ends_with(char *s, char *end);
int				ft_sub_strlen(char *s, char c);
char			*ft_strdup_len_nonl(const char *s1, int len);

void			verify(t_data *data);
void			verify_map_name(int ac, char *av[]);
void			verify_borders(t_map *mapo);
void			verify_enemy_count(t_data *data);
void			verify_map_characters(t_data *data);
void			verify_exit_count(t_data *data);
void			verify_map_width(t_data *data);

#endif