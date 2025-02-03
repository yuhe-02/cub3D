/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 03:52:00 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/03 13:33:42 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	_set_xpm_file_(t_image *image, t_data *data)
{
	image->img = mlx_xpm_file_to_image(data->mlx, image->path,
		&(image->width), &(image->height));
	if (!image->img)
		return (1);
	image->addr = mlx_get_data_addr(image->img, &(image->bpp),
		&(image->llen), &(image->eda));
	return (0);
}

int	_init_data(t_data *data)
{
	data->img.width = WIDTH;
	data->img.height = HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->img.width, data->img.height, "cub3D");
	data->img.img = mlx_new_image(data->mlx, data->img.width, data->img.height);
	data->img.addr = mlx_get_data_addr(data->img.img, &(data->img.bpp), &(data->img.llen),
			&(data->img.eda));
	if (_set_xpm_file_(&(data->tex_north), data))
		return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "north texture not found"));
	if (_set_xpm_file_(&(data->tex_south), data))
		return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "south texture not found"));
	if (_set_xpm_file_(&(data->tex_west), data))
		return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "west texture not found"));
	if (_set_xpm_file_(&(data->tex_east), data))
		return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "east texture not found"));
	return (0);
}
