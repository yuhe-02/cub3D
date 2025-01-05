#include "utils.h"

char world_map[mapWidth][mapHeight + 1] = 
{
  "111111111111111111111111",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000222220000202020001",
  "100000200020000000000001",
  "100000200020000200020001",
  "100000200020000000000001",
  "100000220220000202020001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "122222222000000000000001",
  "120200002000000000000001",
  "120000202000000000000001",
  "120200002000000000000001",
  "120222222000000000000001",
  "120000000000000000000001",
  "122222222000000000000001",
  "111111111111111111111111"
};

// char world_map[mapWidth][mapHeight + 1] = 
// {
//   "111",
//   "101",
//   "111",
// };


void draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
    int y;
	int	relative_height;

    y = 0;
	relative_height = (end - start);
	printf("x: %d, relative height: %d\n", x, relative_height);
	// draw ceiling
	while (y < start)
	{
		ft_mlx_pixel_put(data, x, y, white_16);
        y++;
	}
    while (y <= end)
    {
        ft_mlx_pixel_put(data, x, y, color);
        y++;
    }
	// draw floor
	while (y <= data->img.height)
    {
        ft_mlx_pixel_put(data, x, y, black_16);
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
		ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
		ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
		ray->map_x = (int)(player->pos_x);
		ray->map_y = (int)(player->pos_y);
		if (ray->ray_dir_x == 0)
			ray->delta_dist_x = 1e30;
		else
		{
			ray->delta_dist_x = (1 / ray->ray_dir_x) < 0 ?
			-1 * (1 / ray->ray_dir_x) : (1 / ray->ray_dir_x);
		}
		if (ray->ray_dir_y == 0)
			ray->delta_dist_y = 1e30;
		else
		{
			ray->delta_dist_y = (1 / ray->ray_dir_y) < 0 ?
			-1 * (1 / ray->ray_dir_y) : (1 / ray->ray_dir_y);
		}
		// ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
		// ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
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
		// printf("loop second\n");
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
			// printf("ray map value: %d, %d\n", ray->map_x, ray->map_y);
			if (params->map[ray->map_x][ray->map_y] == '1' || params->map[ray->map_x][ray->map_y] == '2')
				ray->hit = 1;
		}
		// calculate distance of wall
		// if (ray->side == 0)
		// 	ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
		// else
		// 	ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->map_x - player->pos_x +
				(1 - ray->step_x) / 2) / ray->ray_dir_x;
		else
			ray->perp_wall_dist = (ray->map_y - player->pos_y +
				(1 - ray->step_y) / 2) / ray->ray_dir_y;
		line_height = (int)(data->img.height / ray->perp_wall_dist);

		draw_start = -line_height / 2 + data->img.height / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + data->img.height / 2;
		if (draw_end >= data->img.height)
			draw_end = data->img.height - 1;
		
		// set wall color
		if (ray->side == 0)
			color = (ray->step_x > 0) ? red_16 : green_16;
		else
			color = (ray->step_y > 0) ? blue_16 : yellow_16;

		// set wall texture
		if (ray->side == 0)
			image = (ray->step_x > 0) ? &(data->tex_west) : &(data->tex_east);
		else
			image = (ray->step_y > 0) ? &(data->tex_south) : &(data->tex_north);
		// printf("wrinting\n");
		draw_vertical_line(data, x, draw_start, draw_end, color);
		x++;
	}
}

void	update_player(t_params *param, t_player *player)
{
	double move_speed = 0.1;

	if (player->counterclockwise_flag != 0)
	{
		printf("kakudo: %f, %f\n",player->dir_x, player->dir_y);
		double rot_speed = PI / 200;
		double old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(player->counterclockwise_flag * rot_speed) - player->dir_y * sin(player->counterclockwise_flag * rot_speed);
		player->dir_y = old_dir_x * sin(player->counterclockwise_flag * rot_speed) + player->dir_y * cos(player->counterclockwise_flag * rot_speed);

		double old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(player->counterclockwise_flag * rot_speed) - player->plane_y * sin(player->counterclockwise_flag * rot_speed);
		player->plane_y = old_plane_x * sin(player->counterclockwise_flag * rot_speed) + player->plane_y * cos(player->counterclockwise_flag * rot_speed);
	}
	else if (player->horizontal_flag != 0)
	{
		double next_x = player->pos_x + player->horizontal_flag * player->plane_x * move_speed;
		double next_y = player->pos_y + player->horizontal_flag * player->plane_y * move_speed;
		if (param->map[(int)next_x][(int)player->pos_y] == '0')
			player->pos_x = next_x;
		if (param->map[(int)player->pos_x][(int)next_y] == '0')
			player->pos_y = next_y;
	}
	else if (player->vertical_flag != 0)
	{
		double next_x = player->pos_x + player->vertical_flag * player->dir_x * move_speed;
		double next_y = player->pos_y + player->vertical_flag * player->dir_y * move_speed;
		if (param->map[(int)next_x][(int)player->pos_y] == '0')
			player->pos_x = next_x;
		if (param->map[(int)player->pos_x][(int)next_y] == '0')
			player->pos_y = next_y;
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
	mlx_hook(data.win, 17, 0, close_window, &params);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_hook, &params);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, key_release_hook, &params);
	mlx_loop_hook(data.mlx, &main_loop, (void *)&params);
	mlx_loop(data.mlx);
	return (0);
}