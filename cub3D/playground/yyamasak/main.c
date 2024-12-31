#include "utils.h"

// int worldMap[mapWidth][mapHeight] = {
//   {1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},x
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

int worldMap[mapWidth][mapHeight] = {
  {1,2,1},
  {1,2,1},
  {1,2,1},
};

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->llen + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
	return ;
}

void draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
    int y;

    y = start;
    while (y <= end)
    {
        ft_mlx_pixel_put(data, x, y, color);
        y++;
    }
}

void	raycast(t_params *params)
{
	t_data		*data;
	t_player	*player;
	t_ray		*ray;
	int			x;
	int			color;
	int			line_height;
	int			draw_start;
	int			draw_end;

	data = params->data;
	player = params->player;
	ray = params->ray;
	x = 0;
	while (x < data->width)
	{
		/**
		 * memo
		 *  このカメラは、ピクセル(x)が、スクリーンのどの位置にあるのかを-1 , 1の範囲で正規化している。
		 *  左端は、-1,右端は、1になるように計算されている。FOVは90度を前提にしている。
		 */
		ray->camera_x = (2 * x / (double)data->width) - 1;
		ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
		ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
		ray->map_x = (int)(player->pos_x);
		ray->map_y = (int)(player->pos_y);
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
		ray->hit = 0;

		// detect next direction per index and distance
		if (ray->ray_dir_x < 0)
		{
			ray->step_x = -1;
			ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
		}
		else
        {
            ray->step_x = 1;
            ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
        }

		if (ray->ray_dir_y < 0)
		{
			ray->step_y = -1;
			ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
		}
		else
		{
			ray->step_y = 1;
			ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) *ray->delta_dist_y;
		}

		// DDA algorithm
		while (ray->hit == 0)
		{
			if (ray->side_dist_x < ray->side_dist_y)
			{
				ray->side_dist_x += ray->delta_dist_x;
				ray->map_x += ray->step_x;
				ray->side = 0;
			}
			else 
			{
				ray->side_dist_y += ray->delta_dist_y;
				ray->map_y += ray->step_y;
				ray->side = 1;
			}
			if (worldMap[ray->map_x][ray->map_y] > 0)
				ray->hit = 1;
		}

		// calculate distance of wall
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
		else
			ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
		line_height = (int)(data->height / ray->perp_wall_dist);

		draw_start = -line_height / 2 + data->height / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + data->height / 2;
		if (draw_end >= data->height)
			draw_end = data->height - 1;
		
		// set wall color
		color = 0xFFFF00;
        if (worldMap[ray->map_x][ray->map_y] == 1)
            color = 0xFF0000;
        else if (worldMap[ray->map_x][ray->map_y] == 2)
            color = 0x00FF00;
        else if (worldMap[ray->map_x][ray->map_y] == 3)
            color = 0x0000FF;
        else if (worldMap[ray->map_x][ray->map_y] == 4)
            color = 0xFFFFFF;
        // if (ray->side == 1)
        //     color /= 2; // 明るさを調整
		draw_vertical_line(data, x, draw_start, draw_end, color);
		x++;
	}
}

void	update_player(t_params *param, t_player *player)
{
	double move_speed = 0.5;

	if (player->counterclockwise_flag != 0)
	{
		double rot_speed = PI / 4;
		double old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(player->counterclockwise_flag * rot_speed) - player->dir_y * sin(player->counterclockwise_flag * rot_speed);
		player->dir_y = old_dir_x * sin(player->counterclockwise_flag * rot_speed) + player->dir_y * cos(player->counterclockwise_flag * rot_speed);

		double old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(player->counterclockwise_flag * rot_speed) - player->plane_y * sin(player->counterclockwise_flag * rot_speed);
		player->plane_y = old_plane_x * sin(player->counterclockwise_flag * rot_speed) + player->plane_y * cos(player->counterclockwise_flag * rot_speed);
		player->counterclockwise_flag = 0;
	}
	else if (player->horizontal_flag != 0)
	{
		double next_x = player->pos_x + player->horizontal_flag * player->plane_x * move_speed;
		double next_y = player->pos_y + player->horizontal_flag * player->plane_y * move_speed;
		if (param->map[(int)next_x][(int)player->pos_y] == 0)
			player->pos_x = next_x;
		if (param->map[(int)player->pos_x][(int)next_y] == 0)
			player->pos_y = next_y;
		player->horizontal_flag = 0;
	}
	else if (player->vertical_flag != 0)
	{
		double next_x = player->pos_x + player->vertical_flag * player->dir_x * move_speed;
		double next_y = player->pos_y + player->vertical_flag * player->dir_y * move_speed;
		if (param->map[(int)next_x][(int)player->pos_y] == 0)
			player->pos_x = next_x;
		if (param->map[(int)player->pos_x][(int)next_y] == 0)
			player->pos_y = next_y;
		player->vertical_flag = 0;
	}
}
int	main_loop(void *arg)
{
	t_params	*params;
	t_data		*data;
	t_player	*player;

	params = (t_params *)arg;
	data = params->data;
	player = params->player;
	update_player(params, player);
	raycast(params);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_params params;
	t_data data;
	t_player player = {2, 2, -1, 0, 0, 0.66};
	t_ray	ray;

	params.data = &data;
	params.player = &player;
	params.ray = &ray;
	params.map = worldMap;
	params.map_width = mapWidth;
	params.map_height = mapHeight;
	data.width = WIDTH;
	data.height = HEIGHT;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.height, "Raycaster sample");
	data.img = mlx_new_image(data.mlx, data.width, data.height);
	data.addr = mlx_get_data_addr(data.img, &(data.bpp), &(data.llen),
			&(data.eda));
	raycast(&params);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 17, 0, close_window, &params);
	mlx_key_hook(data.win, key_hook, &params);
	mlx_loop_hook(data.mlx, &main_loop, (void *)&params);
	mlx_loop(data.mlx);
	return (0);
}