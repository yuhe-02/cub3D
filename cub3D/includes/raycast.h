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

// typedef struct	s_data {
// 	void		*img;
// 	char		*addr;
// 	int			bpp;
// 	int			llen;
// 	int			eda;
// 	int			width;
// 	int			height;
// }				t_data;

typedef struct s_data
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int llen;
    int eda;
    int			width;
    int			height;
} t_data;

typedef struct s_player
{
    double pos_x;
    double pos_y; // プレイヤー位置
    double dir_x; // 視線方向
    double dir_y;
    double plane_x; // カメラ平面
    double plane_y;
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
    t_data *data;
    t_player *player;
    t_ray   *ray;
}				t_params;

int	key_hook(int keycode, void *arg);
int	close_window(t_params *param);

#endif