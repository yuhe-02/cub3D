/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:49:05 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:49:22 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	_draw_vertical(t_data *data, t_ivec *coord, t_wall *wall)
{
	int		color;
	char	*tex_pixel;

	coord->y = 0;
	while (coord->y < data->img.height)
	{
		if (coord->y < wall->draw_start)
			color = data->ceilling_color;
		else if (coord->y < wall->draw_end)
		{
			wall->tex.y = (int)wall->tex_pos & (wall->target_img->height - 1);
			wall->tex_pos += wall->step;
			tex_pixel = wall->target_img->addr + (wall->tex.y
					* wall->target_img->llen + wall->tex.x
					* (wall->target_img->bpp / 8));
			color = *(int *)tex_pixel;
		}
		else
			color = data->floor_color;
		_ft_mlx_pixel_put(data, coord->x, coord->y, color);
		coord->y++;
	}
}
