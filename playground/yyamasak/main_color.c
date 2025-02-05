#include "raycast.h"

// char world_map[mapWidth][mapHeight + 1] = 
// {
//   "111111111111111111111111",
//   "101000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "111111111111111111111111"
// };

char world_map[mapHeight][mapWidth + 1] = 
{
  "111111",
  "100001",
  "101001",
  "111111"
};


void draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
    int y;
	int	relative_height;

    y = 0;
	relative_height = (end - start);
	// printf("x: %d, relative height: %d\n", x, relative_height);
	// draw ceiling
	while (y < start)
	{
		_ft_mlx_pixel_put(data, x, y, white_16);
        y++;
	}
    while (y <= end)
    {
        _ft_mlx_pixel_put(data, x, y, color);
        y++;
    }
	// draw floor
	while (y <= data->img.height)
    {
        _ft_mlx_pixel_put(data, x, y, black_16);
        y++;
    }
}

void	raycast(t_params *params)
{
	t_data		*data;
	t_player	*player;
	t_ray		*ray;
	t_image		*image;
	int			x;
	int			color;
	int			line_height;
	int			draw_start;
	int			draw_end;

	data = params->data;
	player = params->player;
	ray = params->ray;
	x = 0;
	while (x < data->img.width)
	{
		// printf("loop first\n");
		/**
		 * memo
		 *  このカメラは、ピクセル(x)が、スクリーンのどの位置にあるのかを-1 , 1の範囲で正規化している。
		 *  左端は、-1,右端は、1になるように計算されている。FOVは90度を前提にしている。
		 */
		ray->camera_x = 2 * x / (double)data->img.width - 1;
		ray->ray_dir.x = player->dir.x + player->plane.x * ray->camera_x;
		ray->ray_dir.y = player->dir.y + player->plane.y * ray->camera_x;
		ray->map.x = (int)(player->pos.x);
		ray->map.y = (int)(player->pos.y);
		if (ray->ray_dir.x == 0)
			ray->delta_dist.x = 1e30;
		else
		{
			ray->delta_dist.x = (1 / ray->ray_dir.x) < 0 ?
			-1 * (1 / ray->ray_dir.x) : (1 / ray->ray_dir.x);
		}
		if (ray->ray_dir.y == 0)
			ray->delta_dist.y = 1e30;
		else
		{
			ray->delta_dist.y = (1 / ray->ray_dir.y) < 0 ?
			-1 * (1 / ray->ray_dir.y) : (1 / ray->ray_dir.y);
		}
		// ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
		// ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
		ray->hit = 0;

		// detect next direction per index and distance
		if (ray->ray_dir.x < 0)
		{
			ray->step.x = -1;
			ray->side_dist.x = (player->pos.x - ray->map.x) * ray->delta_dist.x;
		}
		else
        {
            ray->step.x = 1;
            ray->side_dist.x = (ray->map.x + 1.0 - player->pos.x) * ray->delta_dist.x;
        }

		if (ray->ray_dir.y < 0)
		{
			ray->step.y = -1;
			ray->side_dist.y = (player->pos.y - ray->map.y) * ray->delta_dist.y;
		}
		else
		{
			ray->step.y = 1;
			ray->side_dist.y = (ray->map.y + 1.0 - player->pos.y) *ray->delta_dist.y;
		}

		// DDA algorithm
		// printf("loop second\n");
		while (ray->hit == 0)
		{
			if (ray->side_dist.x < ray->side_dist.y)
			{
				ray->side_dist.x += ray->delta_dist.x;
				ray->map.x += ray->step.x;
				ray->side = 0;
			}
			else 
			{
				ray->side_dist.y += ray->delta_dist.y;
				ray->map.y += ray->step.y;
				ray->side = 1;
			}
			// printf("ray map value: %d, %d\n", ray->map.x, ray->map.y);
			// if (params->map[ray->map.x][ray->map.y] == '1' || params->map[ray->map.x][ray->map.y] == '2')
			if (params->map[ray->map.y][ray->map.x] == '1' || params->map[ray->map.y][ray->map.x] == '2')
				ray->hit = 1;
		}
		// calculate distance of wall
		// if (ray->side == 0)
		// 	ray->perp_wall_dist = (ray->side_dist.x - ray->delta_dist.x);
		// else
		// 	ray->perp_wall_dist = (ray->side_dist.y - ray->delta_dist.y);
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->map.x - player->pos.x +
				(1 - ray->step.x) / 2) / ray->ray_dir.x;
		else
			ray->perp_wall_dist = (ray->map.y - player->pos.y +
				(1 - ray->step.y) / 2) / ray->ray_dir.y;
		line_height = (int)(data->img.height / ray->perp_wall_dist);

		draw_start = -line_height / 2 + data->img.height / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + data->img.height / 2;
		if (draw_end >= data->img.height)
			draw_end = data->img.height - 1;
		
		// set wall color
		if (ray->side == 0)
			color = (ray->step.x > 0) ? red_16 : green_16;
		else
			color = (ray->step.y > 0) ? blue_16 : yellow_16;

		// set wall texture
		if (ray->side == 0)
			image = (ray->step.x > 0) ? &(data->tex_west) : &(data->tex_east);
		else
			image = (ray->step.y > 0) ? &(data->tex_south) : &(data->tex_north);
		// printf("wrinting\n");
		draw_vertical_line(data, x, draw_start, draw_end, color);
		x++;
	}
}

void	update_player(t_params *param, t_player *player)
{
	double move_speed = 0.1;

	if (player->rotate_flg != 0)
	{
		printf("kakudo: %f, %f\n",player->dir.x, player->dir.y);
		double rot_speed = PI / 200;
		double old_dir_x = player->dir.x;
		player->dir.x = player->dir.x * cos(player->rotate_flg * rot_speed) - player->dir.y * sin(player->rotate_flg * rot_speed);
		player->dir.y = old_dir_x * sin(player->rotate_flg * rot_speed) + player->dir.y * cos(player->rotate_flg * rot_speed);

		double old_plane_x = player->plane.x;
		player->plane.x = player->plane.x * cos(player->rotate_flg * rot_speed) - player->plane.y * sin(player->rotate_flg * rot_speed);
		player->plane.y = old_plane_x * sin(player->rotate_flg * rot_speed) + player->plane.y * cos(player->rotate_flg * rot_speed);
	}
	else if (player->side_flg != 0)
	{
		double next_x = player->pos.x + player->side_flg * player->plane.x * move_speed;
		double next_y = player->pos.y + player->side_flg * player->plane_y * move_speed;
		if (param->map[(int)player->pos.y][(int)next_x]== '0')
			player->pos.x = next_x;
		if (param->map[(int)next_y][(int)player->pos.x] == '0')
			player->pos.y = next_y;
	}
	else if (player->approx_flg != 0)
	{
		double next_x = player->pos.x + player->approx_flg * player->dir.x * move_speed;
		double next_y = player->pos.y + player->approx_flg * player->dir.y * move_speed;
		if (param->map[(int)player->pos.y][(int)next_x] == '0')
			player->pos.x = next_x;
		if (param->map[(int)next_y][(int)player->pos.x] == '0')
			player->pos.y = next_y;
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
	if (data->mlx && data->win && data->img.img)
		ft_bzero(data->img.addr, data->img.llen * data->img.height);
	update_player(params, player);
	raycast(params);
	if (data->mlx && data->win && data->img.img)
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

int	main(void)
{
	t_params	params;
	t_data		data;
	t_player	player;
	t_ray		ray;

	params.data = &data;
	params.ray = &ray;
	params.player = &player;
	init_data(params.data);
	init_player(&player, 2, 2);
	init_params(&params, &data, &ray, &player, world_map);
	mlx_hook(data.win, 17, 0, _close_window, &params);
	mlx_hook(data.win, KeyPress, KeyPressMask, _key_hook, &params);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, _key_release_hook, &params);
	mlx_loop_hook(data.mlx, &main_loop, (void *)&params);
	mlx_loop(data.mlx);
	return (0);
}