#include "utils.h"

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
        ray->side_dist.x = (ray->map.x + 1.0 - player_pos->x) * ray->delta_dist.x;
    }
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player_pos->y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - player_pos->y) *ray->delta_dist.y;
	}

}

void	_ray_assign(t_ray *ray, t_data *data, t_player *player, t_ivec *coord)
{
	ray->camera_x = 2.0 * coord->x / (double)data->img.width - 1.0;
	_vector_assign(&(ray->ray_dir), player->dir.x + player->plane.x * ray->camera_x, player->dir.y + player->plane.y * ray->camera_x);
	_ivec_assign(&(ray->map), (int)(player->pos.x), (int)(player->pos.y));
	_vector_assign(&(ray->delta_dist),fabs(1 / ray->ray_dir.x), fabs(1 / ray->ray_dir.y));
	ray->hit = 0;
	_detect_ray_diretion_(ray, &(player->pos));
}