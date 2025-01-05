#ifndef RAYCAST_H
# define RAYCAST_H

# include <stdio.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stddef.h>
# include <unistd.h>
# include <math.h>
# include <stdint.h>
#include <fcntl.h>//add
#include <string.h>//add
#include <errno.h>//add
#include <ctype.h>//add
# include "../minilibx-linux/mlx.h"
# include "../gnl/get_next_line.h"

# define WIDTH 800
# define HEIGHT 800
# define WINDOW_NAME "test"
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_R_DIR 65363
# define KEY_L_DIR 65361
# define WINDOW_CLOSE 17
# define ACRAC 1000
# define mapWidth 24
# define mapHeight 24
# define red_16 0xFF0000
# define blue_16 0x0000FF
# define yellow_16 0xFFFF00
# define green_16 0x00FF00
# define black_16 0x000000
# define white_16 0xFFFFFF
# define PI 3.141582653589793

typedef struct s_image
{
    void *img;
    char *addr;
    int bpp;
    int llen;
    int eda;
    int	width;
    int	height;
}               t_image;

typedef struct s_data
{
    void    *mlx;
    void    *win;
    t_image img;
    t_image tex_north;
    t_image tex_south;
    t_image tex_west;
    t_image tex_east;
} t_data;

typedef struct s_player
{
    double pos_x;
    double pos_y; // プレイヤー位置
    double dir_x; // 視線方向
    double dir_y;
    double plane_x; // カメラ平面
    double plane_y;
    int     horizontal_flag;
    int     vertical_flag;
    int     counterclockwise_flag;

}  				t_player;

typedef struct s_ray
{
    double	camera_x;
    double	ray_dir_x;
    double	ray_dir_y;
    int		map_x;
    int		map_y;
    double	side_dist_x;
    double 	side_dist_y;
    double	delta_dist_x;
    double	delta_dist_y;
    double	perp_wall_dist;
    int		step_x;
    int		step_y;
    int		hit;
    int		side;
}			t_ray;

typedef struct s_vector {
	double		x;
	double		y;

}				t_vector;

typedef struct	s_params
{
    t_data      *data;
    t_player    *player;
    t_ray       *ray;
    char        (*map)[mapWidth + 1];
    int         map_width;
    int         map_height;


}				t_params;

int     key_hook(int keycode, void *arg);
int		key_release_hook(int keycode, t_params *param);
int     close_window(t_params *param);
void	ft_mlx_pixel_put(t_data *data, int x, int y, int color);
void	init_params(t_params* params, t_data *data, t_ray *ray, t_player *player, char (*world_map)[mapWidth + 1]);
void	init_data(t_data *data);
void	init_player(t_player *player, int x, int y);
double	convert_to_radian(int degree);
int		convert_to_degree(double radian);

#endif