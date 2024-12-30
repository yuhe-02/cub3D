#include "utils.h"

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void my_mlx_pixel_put(t_data *data, int x, int y, int color) 
{
    char *dst;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = data->addr + (y * data->llen + x * (data->bpp / 8));
        *(unsigned int *)dst = color;
    }
}

void draw_vertical_line(t_data *data, int x, int start, int end, int color) {
    int y;

    y = start;
    while (y <= end)
    {
        my_mlx_pixel_put(data, x, y, color);
        y++;
    }
}

void raycast(t_data *data, t_player *player)
{
    int		x;
    int		color;
    t_ray	ray;
    int		line_height;
    int		draw_start;
    int		draw_end;

    x = 0;
    while (x < WIDTH)
    {
        ray.camera_x = 2 * x / (double)WIDTH - 1;
        ray.ray_dir_x = player->dir_x + player->plane_x * ray.camera_x;
        ray.ray_dir_y = player->dir_y + player->plane_y * ray.camera_x;
        ray.map_x = (int)player->pos_x;
        ray.map_y = (int)player->pos_y;
        ray.delta_dist_x = fabs(1 / ray.ray_dir_x);
        ray.delta_dist_y = fabs(1 / ray.ray_dir_y);
        ray.hit = 0;

        if (ray.ray_dir_x < 0)
        {
            ray.step_x = -1;
            ray.side_dist_x = (player->pos_x - ray.map_x) * ray.delta_dist_x;
        } 
        else
        {
            ray.step_x = 1;
            ray.side_dist_x = (ray.map_x + 1.0 - player->pos_x) * ray.delta_dist_x;
        }

        if (ray.ray_dir_y < 0)
        {
            ray.step_y = -1;
            ray.side_dist_y = (player->pos_y - ray.map_y) * ray.delta_dist_y;
        } 
        else
        {
            ray.step_y = 1;
            ray.side_dist_y = (ray.map_y + 1.0 - player->pos_y) * ray.delta_dist_y;
        }

        // DDAアルゴリズム
        while (ray.hit == 0)
        {
            if (ray.side_dist_x < ray.side_dist_y)
            {
                ray.side_dist_x += ray.delta_dist_x;
                ray.map_x += ray.step_x;
                ray.side = 0;
            }
            else
            {
                ray.side_dist_y += ray.delta_dist_y;
                ray.map_y += ray.step_y;
                ray.side = 1;
            }
            if (worldMap[ray.map_x][ray.map_y] > 0) 
                ray.hit = 1;
        }

        // 壁の距離計算
        if (ray.side == 0)
            ray.perp_wall_dist = (ray.side_dist_x - ray.delta_dist_x);
        else
            ray.perp_wall_dist = (ray.side_dist_y - ray.delta_dist_y);

        line_height = (int)(HEIGHT / ray.perp_wall_dist);

        draw_start = -line_height / 2 + HEIGHT / 2;
        if (draw_start < 0) 
            draw_start = 0;

        draw_end = line_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT) 
            draw_end = HEIGHT - 1;

        // 壁の色設定
        color = 0xFFFF00;
        if (worldMap[ray.map_x][ray.map_y] == 1)
            color = 0xFF0000;
        else if (worldMap[ray.map_x][ray.map_y] == 2)
            color = 0x00FF00;
        else if (worldMap[ray.map_x][ray.map_y] == 3)
            color = 0x0000FF;
        else if (worldMap[ray.map_x][ray.map_y] == 4)
            color = 0xFFFFFF;
        if (ray.side == 1)
            color /= 2; // 明るさを調整
        draw_vertical_line(data, x, draw_start, draw_end, color);
        x++;
    }
}

int main()
{
    t_data data;
    t_player player = {22, 12, -1, 0, 0, 0.66};
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Raycaster");
    data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.llen, &data.eda);
    raycast(&data, &player);
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_loop(data.mlx);
    return 0;
}