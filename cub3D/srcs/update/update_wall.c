#include "utils.h"


static void _set_wall_tex_(t_image **target_img, t_ray *ray, t_data *data)
{
	if (ray->side == 0)
	{
		if (ray->step.x > 0)
			*target_img = &(data->tex_west);
		else
			*target_img = &(data->tex_east);
	}		
	else
	{
		if (ray->step.y > 0)
			*target_img = &(data->tex_north);
		else
			*target_img = &(data->tex_south);
	}		
}

void	_wall_assign(t_wall *wall, t_data *data, t_ray *ray, t_player *player)
{
	wall->line_height = (int)(data->img.height / ray->perp_wall_dist);
	wall->draw_start = -wall->line_height / 2 + data->img.height / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + data->img.height / 2;
	if (wall->draw_end >= data->img.height)
		wall->draw_end = data->img.height - 1;
	// set wall texture
	_set_wall_tex_(&(wall->target_img), ray, data);
	if (ray->side == 0)
		wall->wall_x = player->pos.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		wall->wall_x = player->pos.x + ray->perp_wall_dist * ray->ray_dir.x;
	wall->wall_x -= floor(wall->wall_x);
	wall->tex.x = (int)(wall->wall_x * (double)wall->target_img->width);
	if (ray->side == 0 && ray->ray_dir.x > 0)
		wall->tex.x = wall->target_img->width - wall->tex.x - 1;
	if (ray->side == 1 && ray->ray_dir.y < 0)
		wall->tex.x = wall->target_img->width - wall->tex.x - 1;
	// draw the pixels of the stripe as a vertical line
	wall->step = 1.0 * wall->target_img->height / wall->line_height;
	wall->tex_pos = (wall->draw_start - data->img.height / 2 + wall->line_height / 2) * wall->step;
}
