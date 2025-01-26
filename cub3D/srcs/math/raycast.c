#include "utils.h"


// DDA algo
static void _calc_hit_pos_(t_params *params, t_ray *ray)
{
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
		if (params->map[ray->map.y][ray->map.x] == '1' || params->map[ray->map.y][ray->map.x] == '2')
			ray->hit = 1;
	}
}

void	_raycast(t_params *params)
{
	t_data		*data;
	t_player	*player;
	t_ray		*ray;
	t_ivec		coord;
	t_wall		wall;

	data = params->data;
	player = params->player;
	ray = params->ray;
	coord.x = 0;
	while (coord.x < data->img.width)
	{
		// printf("loop first\n");
		/**
		 * memo
		 *  このカメラは、ピクセル(x)が、スクリーンのどの位置にあるのかを-1 , 1の範囲で正規化している。
		 *  左端は、-1,右端は、1になるように計算されている。FOVは90度を前提にしている。
		 */
		ray->camera_x = 2 * coord.x / (double)data->img.width - 1;
		ray->ray_dir.x = player->dir.x + player->plane.x * ray->camera_x;
		ray->ray_dir.y = player->dir.y + player->plane.y * ray->camera_x;
		ray->map.x = (int)(player->pos.x);
		ray->map.y = (int)(player->pos.y);
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
		_calc_hit_pos_(params, ray);
		// calculate distance of wall
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->map.x - player->pos.x +
				(1 - ray->step.x) / 2) / ray->ray_dir.x;
		else
			ray->perp_wall_dist = (ray->map.y - player->pos.y +
				(1 - ray->step.y) / 2) / ray->ray_dir.y;
		wall.line_height = (int)(data->img.height / ray->perp_wall_dist);

		wall.draw_start = -wall.line_height / 2 + data->img.height / 2;
		if (wall.draw_start < 0)
			wall.draw_start = 0;
		wall.draw_end = wall.line_height / 2 + data->img.height / 2;
		if (wall.draw_end >= data->img.height)
			wall.draw_end = data->img.height - 1;
		
		// set wall texture
		if (ray->side == 0)
			wall.target_img = (ray->step.x > 0) ? &(data->tex_west) : &(data->tex_east);
		else
			wall.target_img = (ray->step.y > 0) ? &(data->tex_north) : &(data->tex_south);
		if (ray->side == 0)
			wall.wall_x = player->pos.y + ray->perp_wall_dist * ray->ray_dir.y;
		else
			wall.wall_x = player->pos.x + ray->perp_wall_dist * ray->ray_dir.x;
		wall.wall_x -= floor(wall.wall_x);

		wall.tex.x = (int)(wall.wall_x * (double)wall.target_img->width);
		if (ray->side == 0 && ray->ray_dir.x > 0)
			wall.tex.x = wall.target_img->width - wall.tex.x - 1;
		if (ray->side == 1 && ray->ray_dir.y < 0)
			wall.tex.x = wall.target_img->width - wall.tex.x - 1;

		// draw the pixels of the stripe as a vertical line
		wall.step = 1.0 * wall.target_img->height / wall.line_height;
		wall.tex_pos = (wall.draw_start - data->img.height / 2 + wall.line_height / 2) * wall.step;

		// contents drawer
		_draw_vertical(data, &coord, &wall);
		coord.x++;
	}
}
