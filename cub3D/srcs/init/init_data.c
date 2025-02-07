/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 03:52:00 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:51:39 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static int	_check_open_file_(char *path)
{
	int	fd;

	if (!path)
		return (1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

static int	_check_path_is_valid_(t_data *data)
{
	if (_check_open_file_(data->tex_north.path))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOTEX));
	if (_check_open_file_(data->tex_south.path))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOTEX));
	if (_check_open_file_(data->tex_west.path))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOTEX));
	if (_check_open_file_(data->tex_east.path))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOTEX));
	return (0);
}

static int	_set_xpm_file_(t_image *image, t_data *data)
{
	image->img = mlx_xpm_file_to_image(data->mlx, image->path, &(image->width),
			&(image->height));
	if (!image->img)
		return (1);
	image->addr = mlx_get_data_addr(image->img, &(image->bpp), &(image->llen),
			&(image->eda));
	return (0);
}

int	_init_data(t_data *data)
{
	if (_check_path_is_valid_(data))
		return (1);
	printf("%s\n", data->tex_north.path);
	data->img.width = WIDTH;
	data->img.height = HEIGHT;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR3, ERR_MLX));
	data->win = mlx_new_window(data->mlx, data->img.width, data->img.height,
			"cub3D");
	data->img.img = mlx_new_image(data->mlx, data->img.width, data->img.height);
	data->img.addr = mlx_get_data_addr(data->img.img, &(data->img.bpp),
			&(data->img.llen), &(data->img.eda));
	if (_set_xpm_file_(&(data->tex_north), data))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOTEX));
	if (_set_xpm_file_(&(data->tex_south), data))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOTEX));
	if (_set_xpm_file_(&(data->tex_west), data))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOTEX));
	if (_set_xpm_file_(&(data->tex_east), data))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOTEX));
	return (0);
}
