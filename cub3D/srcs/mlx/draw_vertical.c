#include "utils.h"

void	_draw_vertical(t_data *data, t_ivec *coord, t_wall *wall)
{
	int	color;

	coord->y = 0;
	while (coord->y < data->img.height)
	{
		if (coord->y < wall->draw_start)
			color = white_16;
		else if (coord->y < wall->draw_end)
		{
			wall->tex.y = (int)wall->tex_pos & (wall->target_img->height - 1);
			wall->tex_pos += wall->step;
			// Calculate pixel position in the texture
			char *tex_pixel = wall->target_img->addr + (wall->tex.y * wall->target_img->llen + wall->tex.x * (wall->target_img->bpp / 8));
			// Convert texture pixel color (assuming 32-bit color depth)
			color = *(int *)tex_pixel;
		}
		else
			color = black_16;
		_ft_mlx_pixel_put(data, coord->x, coord->y, color);
		coord->y++;
	}
}
