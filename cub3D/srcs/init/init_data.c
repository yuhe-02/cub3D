/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 03:52:00 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/24 16:53:51 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	_init_data(t_data *data)
{
	char *north_path = "../../walls/north.xpm";
	char *south_path = "../../walls/south.xpm";
	char *west_path  = "../../walls/west.xpm";
	char *east_path  = "../../walls/east.xpm";

	data->img.width = WIDTH;
	data->img.height = HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->img.width, data->img.height, "Raycaster sample");
	data->img.img = mlx_new_image(data->mlx, data->img.width, data->img.height);
	data->img.addr = mlx_get_data_addr(data->img.img, &(data->img.bpp), &(data->img.llen),
			&(data->img.eda));
	data->tex_north.img = mlx_xpm_file_to_image(data->mlx, north_path,
		&(data->tex_north.width), &(data->tex_north.height));
	data->tex_north.addr = mlx_get_data_addr(data->tex_north.img, &(data->tex_north.bpp),
		&(data->tex_north.llen), &(data->tex_north.eda));
	data->tex_south.img = mlx_xpm_file_to_image(data->mlx, south_path,
		&(data->tex_south.width), &(data->tex_south.height));
	data->tex_south.addr = mlx_get_data_addr(data->tex_south.img, &(data->tex_south.bpp),
		&(data->tex_south.llen), &(data->tex_south.eda));

	data->tex_west.img = mlx_xpm_file_to_image(data->mlx, west_path,
		&(data->tex_west.width), &(data->tex_west.height));
	data->tex_west.addr = mlx_get_data_addr(data->tex_west.img, &(data->tex_west.bpp),
		&(data->tex_west.llen), &(data->tex_west.eda));

	data->tex_east.img = mlx_xpm_file_to_image(data->mlx, east_path,
		&(data->tex_east.width), &(data->tex_east.height));
	data->tex_east.addr = mlx_get_data_addr(data->tex_east.img, &(data->tex_east.bpp),
		&(data->tex_east.llen), &(data->tex_east.eda));
}