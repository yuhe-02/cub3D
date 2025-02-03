#include "raycast.h"

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
// TODO なんでこの計算で行けるんだっけ、内側に行っている部分がよくわからないから上の関数と照らし合わせて理解する
static double	calc_wall_distance_(t_ray *ray)
{
	double	dis;

	// if (ray->side == 0)
	// 	dis = (ray->map.x - player->pos.x + (1 - ray->step.x) / 2) / ray->ray_dir.x;
	// else
	// 	dis = (ray->map.y - player->pos.y + (1 - ray->step.y) / 2) / ray->ray_dir.y;
	if (ray->side == 0)
		dis = ray->side_dist.x - ray->delta_dist.x;
	else
		dis = ray->side_dist.y - ray->delta_dist.y;
	return (dis);
}
// TODO ｙ座標の進行方向とインデックスの運用が逆なのになんでうまく行っているのか調査する
// TODO なぜ魚眼効果が起きるのか
/**
 * while文は、表示されている画面の左側から右側までを表している。
 * camera_xは、coord.xが、スクリーンのどの位置にあるのかを-1 , 1の範囲で正規化している。
 * 左端は、-1,右端は、1になるように計算されている。FOVは90度を前提にしている。
 * ray_dirは、rayの方向を表している。()
 * delta_distは、rayが各成分方向に１単位増加させるにあたって何倍すればいいのかを求めている
 * side_distは、現在位置からｘ、ｙそれぞれの次のインデックスに行くまでに必要な値を求めている
 * perp_wall_distｈ，壁までの垂直距離を求めている（なぜ魚眼効果が起きるのか）
 */
void	_raycast(t_params *params)
{
	t_data		*data;
	t_player	*player;
	t_ray		*ray;
	t_ivec		coord;
	t_wall		wall;

	data = &(params->data);
	player = &(params->player);
	ray = &(params->ray);
	coord.x = 0;
	while (coord.x < data->img.width)
	{
		_ray_assign(ray, data, player, &coord);
		// DDA algorithm
		_calc_hit_pos_(params, ray);
		// calculate distance of wall
		ray->perp_wall_dist = calc_wall_distance_(ray);
		_wall_assign(&wall, data, ray, player);
		// contents drawer
		_draw_vertical(data, &coord, &wall);
		coord.x++;
	}
}
