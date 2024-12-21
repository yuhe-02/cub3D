#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stddef.h>
# include <unistd.h>
# include <math.h>
# include <stdint.h>
#include "../minilibx-linux/mlx.h"

# define WIDTH 800
# define HEIGHT 800
# define WINDOW_NAME "test"

typedef struct	s_data {
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    double zoom;
    double offsetX;
    double offsetY;
}				t_data;

#define ACRAC 1000

#endif