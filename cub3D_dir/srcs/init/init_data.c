/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 03:52:00 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/02 16:40:32 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	_set_xpm_file_(t_image *image, t_data *data)
{
	image->img = mlx_xpm_file_to_image(data->mlx, image->path,
		&(image->width), &(image->height));
	if (!image->img)
		return (0);
	image->addr = mlx_get_data_addr(image->img, &(image->bpp),
		&(image->llen), &(image->eda));
	return (1);
}

void	_init_data(t_data *data)
{
	data->img.width = WIDTH;
	data->img.height = HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->img.width, data->img.height, "cub3D");
	data->img.img = mlx_new_image(data->mlx, data->img.width, data->img.height);
	data->img.addr = mlx_get_data_addr(data->img.img, &(data->img.bpp), &(data->img.llen),
			&(data->img.eda));
	if (!_set_xpm_file_(&(data->tex_north), data))
		error_exit("image not found\n", 1);
	if (!_set_xpm_file_(&(data->tex_south), data))
		error_exit("image not found\n", 1);
	if (!_set_xpm_file_(&(data->tex_west), data))
		error_exit("image not found\n", 1);
	if (!_set_xpm_file_(&(data->tex_east), data))
		error_exit("image not found\n", 1);
}
