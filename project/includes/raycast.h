/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:56:28 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 01:01:08 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "../ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../srcs/gnl/get_next_line.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 400
# define HEIGHT 400
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_R_DIR 65363
# define KEY_L_DIR 65361
# define WINDOW_CLOSE 17
# define PI 3.141582653589793
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.0157079133
# define ERR_FD 2

# define ERR1 "Invalid map: "
# define ERR_EDGE "player or field not locate map edge"
# define ERR_EMPTY "player or field not locate near space"
# define ERR_ASCII "found not valid ascii"
# define ERR_EMPTY_LINE "empty line found in map"
# define ERR2 "Invalid settings: "
# define ERR_NOPATH "some texture not set"
# define ERR_NOCOLOR "floor or ceiling color not set"
# define ERR_NOCOLORFORM "color have to be set as number split by ,"
# define ERR_NOPLAYER "player position not set"
# define ERR_NOTEX "some texture failed to open"
# define ERR_DUBTEX "same texture settings cannot be applied more than once"
# define ERR_DUBPAR "same parameter settings cannot be applied more than once"
# define ERR_NOEXT "invalid extensions"
# define ERR3 "Unexpected error: "
# define ERR_MLX "mlx init failed"
# define ERR_ALLOC "malloc failed"
# define ERR_OPEN "open file failed"

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_ivec
{
	int			x;
	int			y;
}				t_ivec;

typedef struct s_image
{
	void		*img;
	char		*addr;
	char		*path;
	int			bpp;
	int			llen;
	int			eda;
	int			width;
	int			height;
}				t_image;

typedef struct s_wall
{
	t_image		*target_img;
	int			line_height;
	double		wall_x;
	t_ivec		tex;
	int			draw_start;
	int			draw_end;
	double		step;
	double		tex_pos;
}				t_wall;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_image		tex_north;
	t_image		tex_south;
	t_image		tex_west;
	t_image		tex_east;
	int			ceilling_color;
	int			floor_color;
}				t_data;

typedef struct s_player
{
	t_vector	dir;
	t_vector	pos;
	t_vector	plane;
	int			side_flg;
	int			approx_flg;
	int			rotate_flg;
	int			init_userdir_x;
	int			init_userdir_y;
	int			init_userpos_x;
	int			init_userpos_y;
}				t_player;

typedef struct s_ray
{
	double		camera_x;
	t_vector	ray_dir;
	t_vector	side_dist;
	t_vector	delta_dist;
	t_ivec		map;
	t_ivec		step;
	double		perp_wall_dist;
	int			hit;
	int			side;
}				t_ray;

typedef struct s_map_info
{
	char		current;
	char		next;
	char		above;
	char		bottom;
	int			y;
	int			x;
}				t_map_info;

typedef struct s_params
{
	t_data		data;
	t_player	player;
	t_ray		ray;
	char		**map;
	int			map_width;
	int			map_height;
}				t_params;

int				_key_hook(int keycode, void *arg);
int				_key_release_hook(int keycode, t_params *param);
int				_close_window(t_params *param);
void			_ft_mlx_pixel_put(t_data *data, int x, int y, int color);
int				_init_params(t_params **params);
int				_init_data(t_data *data);
void			_init_player(t_player *player);
void			_update_player(t_params *param, t_player *player);
void			_vector_assign(t_vector *vector, double new_x, double new_y);
void			_ivec_assign(t_ivec *ivec, int new_x, int new_y);
void			_ray_assign(t_ray *ray, t_data *data, t_player *player,
					t_ivec *coord);
void			_wall_assign(t_wall *wall, t_data *data, t_ray *ray,
					t_player *player);
double			convert_to_radian(int degree);
int				convert_to_degree(double radian);
void			set_event(t_data *data, t_params *params);
void			_raycast(t_params *params);
void			_draw_vertical(t_data *data, t_ivec *coord, t_wall *wall);
void			error_exit(const char *str, int error_num);
int				_check_valid_map(int len, int start_index, char **line);

// ryomori
int				parse_color(char *line, int *color);
int				_parse_map_settings(char **line, t_params *params);
int				_parse_map_data(char **line, int start_index, t_params *params);
int				_parse(const char *map_file, t_params *params);
int				_parse_map(char **line, t_params *params);
int				is_valid_ascii(char c);
int				is_space(int c);
int				is_user_dir(char c);
int				is_field(char c);
int				calc_max_width(t_params *params, int start_index, char **line);
int				count_map_height(int start_index, char **line);

#endif