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

static double	calc_wall_distance_(t_ray *ray, t_player *player)
{
	double	dis;
	if (ray->side == 0)
		dis = (ray->map.x - player->pos.x + (1 - ray->step.x) / 2) / ray->ray_dir.x;
	else
		dis = (ray->map.y - player->pos.y + (1 - ray->step.y) / 2) / ray->ray_dir.y;
	return (dis);
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
		_ray_assign(ray, data, player, &coord);
		// DDA algorithm
		_calc_hit_pos_(params, ray);
		// calculate distance of wall
		ray->perp_wall_dist = calc_wall_distance_(ray, player);
		_wall_assign(&wall, data, ray, player);
		// contents drawer
		_draw_vertical(data, &coord, &wall);
		coord.x++;
	}
}
