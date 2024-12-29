#include "utils.h"

// int main() {
//     t_params    params;
//     char str[] = "../../walls/north.xpm";

//     memset(&params, 0, sizeof(t_params));
//     params.mlx = mlx_init();
//     params.win = mlx_new_window(params.mlx, WIDTH, HEIGHT, "XPM Image Example");
//     params.data.img = mlx_xpm_file_to_image(params.mlx, str, &(params.data.width), &(params.data.height));
//     mlx_put_image_to_window(params.mlx, params.win, params.data.img, WIDTH / 2 - 32, HEIGHT / 2 - 32);
//     mlx_hook(params.win, WINDOW_CLOSE, 0, close_window, &(params));
//     mlx_key_hook(params.win, key_hook, &(params));
//     mlx_loop(params.mlx);
//     return (0);
// }

// #include <math.h>
// #include <mlx.h>
// #include <stdlib.h>
// #include <stdint.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 10
#define MAP_HEIGHT 10

typedef struct {
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
    t_vector pos;
    t_vector dir;
    t_vector plane;
    int map[MAP_HEIGHT][MAP_WIDTH];
} t_game;

void my_mlx_pixel_put(t_game *game, int x, int y, int color) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        char *dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
        *(unsigned int *)dst = color;
    }
}

void draw_vertical_line(t_game *game, int x, int start, int end, int color) {
    for (int y = start; y <= end; y++) {
        my_mlx_pixel_put(game, x, y, color);
    }
}

void render_frame(t_game *game) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        t_vector ray_dir = {game->dir.x + game->plane.x * camera_x, game->dir.y + game->plane.y * camera_x};
        int map_x = (int)game->pos.x;
        int map_y = (int)game->pos.y;
        double delta_dist_x = fabs(1 / ray_dir.x);
        double delta_dist_y = fabs(1 / ray_dir.y);
        double side_dist_x, side_dist_y;

        int step_x, step_y;
        if (ray_dir.x < 0) {
            step_x = -1;
            side_dist_x = (game->pos.x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->pos.x) * delta_dist_x;
        }
        if (ray_dir.y < 0) {
            step_y = -1;
            side_dist_y = (game->pos.y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->pos.y) * delta_dist_y;
        }

        int hit = 0, side;
        while (!hit) {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (game->map[map_y][map_x] == 1)
                hit = 1;
        }

        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (map_x - game->pos.x + (1 - step_x) / 2) / ray_dir.x;
        else
            perp_wall_dist = (map_y - game->pos.y + (1 - step_y) / 2) / ray_dir.y;

        int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
        int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_end >= SCREEN_HEIGHT) draw_end = SCREEN_HEIGHT - 1;

        int color = (side == 0) ? 0xFF0000 : 0x00FF00;
        draw_vertical_line(game, x, draw_start, draw_end, color);
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int key_hook(int keycode, t_game *game) {
    if (keycode == 65307) // ESC
        exit(0);
    return 0;
}

int main() {
    t_game game;
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycasting");
    game.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    game.addr = mlx_get_data_addr(game.img, &game.bpp, &game.line_len, &game.endian);

    game.pos = (t_vector){5.0, 5.0};
    game.dir = (t_vector){-1.0, 0.0};
    game.plane = (t_vector){0.0, 0.66};

    int map[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };
    memcpy(game.map, map, sizeof(map));

    mlx_loop_hook(game.mlx, (int (*)(void *))render_frame, &game);
    mlx_key_hook(game.win, key_hook, &game);
    mlx_loop(game.mlx);
    return 0;
}


