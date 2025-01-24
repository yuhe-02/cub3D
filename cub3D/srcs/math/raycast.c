#include "utils.h"

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
		// if (ray->ray_dir.x == 0)
		// 	ray->delta_dist.x = 1e30;
		// else
		// {
		// 	ray->delta_dist.x = (1 / ray->ray_dir.x) < 0 ?
		// 	-1 * (1 / ray->ray_dir.x) : (1 / ray->ray_dir.x);
		// }
		// if (ray->ray_dir.y == 0)
		// 	ray->delta_dist.y = 1e30;
		// else
		// {
		// 	ray->delta_dist.y = (1 / ray->ray_dir.y) < 0 ?
		// 	-1 * (1 / ray->ray_dir.y) : (1 / ray->ray_dir.y);
		// }
		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
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
			image = (ray->step.y > 0) ? &(data->tex_north) : &(data->tex_south);
		// printf("wrinting\n");
		// draw_vertical_line(data, x, draw_start, draw_end, color);
				// calculate texture X coordinate
		double wall_x;
		if (ray->side == 0)
			wall_x = player->pos.y + ray->perp_wall_dist * ray->ray_dir.y;
		else
			wall_x = player->pos.x + ray->perp_wall_dist * ray->ray_dir.x;
		wall_x -= floor(wall_x);

		int tex_x = (int)(wall_x * (double)image->width);
		if (ray->side == 0 && ray->ray_dir.x > 0)
			tex_x = image->width - tex_x - 1;
		if (ray->side == 1 && ray->ray_dir.y < 0)
			tex_x = image->width - tex_x - 1;

		// draw the pixels of the stripe as a vertical line
		double step = 1.0 * image->height / line_height;
		double tex_pos = (draw_start - data->img.height / 2 + line_height / 2) * step;

		// contens drawer
		int y = 0;
		while (y < draw_start)
		{
			ft_mlx_pixel_put(data, x, y, white_16);
			y++;
		}
		while (y < draw_end)
		{
			int tex_y = (int)tex_pos & (image->height - 1);
			tex_pos += step;
			// Calculate pixel position in the texture
			char *tex_pixel = image->addr + (tex_y * image->llen + tex_x * (image->bpp / 8));
			// Convert texture pixel color (assuming 32-bit color depth)
			int color = *(int *)tex_pixel;
			// Set pixel to image buffer
			ft_mlx_pixel_put(data, x, y, color);
			y++;
		}
		while (y < data->img.height)
		{
			ft_mlx_pixel_put(data, x, y, black_16);
			y++;
		}
		x++;
	}
}