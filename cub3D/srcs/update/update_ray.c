/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:30:52 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:30:55 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	_detect_ray_diretion_(t_ray *ray, t_vector *player_pos)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player_pos->x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - player_pos->x)
			* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player_pos->y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - player_pos->y)
			* ray->delta_dist.y;
	}
}

void	_ray_assign(t_ray *ray, t_data *data, t_player *player, t_ivec *coord)
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dir_x;
	double	delta_dir_y;

	ray->camera_x = 2.0 * coord->x / (double)data->img.width - 1.0;
	ray_dir_x = player->dir.x + player->plane.x * ray->camera_x;
	ray_dir_y = player->dir.y + player->plane.y * ray->camera_x;
	if (ray_dir_x == 0)
		delta_dir_x = 1e30;
	else
		delta_dir_x = fabs(1 / ray->ray_dir.x);
	if (ray_dir_y == 0)
		delta_dir_y = 1e30;
	else
		delta_dir_y = fabs(1 / ray->ray_dir.y);
	_vector_assign(&(ray->ray_dir), ray_dir_x, ray_dir_y);
	_ivec_assign(&(ray->map), (int)(player->pos.x), (int)(player->pos.y));
	_vector_assign(&(ray->delta_dist), delta_dir_x, delta_dir_y);
	ray->hit = 0;
	_detect_ray_diretion_(ray, &(player->pos));
}
