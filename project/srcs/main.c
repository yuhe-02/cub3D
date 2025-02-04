/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:54:54 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:55:39 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int	main_loop(void *arg)
{
	t_params	*params;
	t_data		*data;
	t_player	*player;

	params = (t_params *)arg;
	data = &(params->data);
	player = &(params->player);
	if (data->mlx && data->win && data->img.img)
		ft_bzero(data->img.addr, data->img.llen * data->img.height);
	_update_player(params, player);
	_raycast(params);
	if (data->mlx && data->win && data->img.img)
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

static int	check_all_set_(t_params *params)
{
	if (!params->data.tex_north.path)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOPATH));
	if (!params->data.tex_south.path)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOPATH));
	if (!params->data.tex_west.path)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOPATH));
	if (!params->data.tex_east.path)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOPATH));
	if (params->data.ceilling_color == -1)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOCOLOR));
	if (params->data.floor_color == -1)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOCOLOR));
	if (params->player.init_userpos_x == -1)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOPLAYER));
	return (0);
}
// static void call_struct(t_params *params)
// {
// 	printf("mapwidth, mapheight = (%d, %d)\n", params->map_width,
//		params->map_height);
// 	printf("path north: %s\n", params->data.tex_north.path);
// 	printf("path south: %s\n", params->data.tex_south.path);
// 	printf("path west: %s\n", params->data.tex_west.path);
// 	printf("path east: %s\n", params->data.tex_east.path);
// 	printf("ceiling, floor=(%x, %x)\n", params->data.ceilling_color,
//		params->data.floor_color);
// 	printf("player pos=(%d, %d)\n", params->player.init_userpos_x,
//		params->player.init_userpos_y);
// }

int	main(int argc, char **argv)
{
	t_params	*params;

	if (argc == 1)
		error_exit("need arguments\n", 1);
	if (argc != 2)
		error_exit("too many arguments\n", 1);
	if (_init_params(&params))
		exit(1);
	if (_parse(argv[1], params))
		exit(1);
	if (check_all_set_(params))
		exit(1);
	if (_init_data(&(params->data)))
		exit(1);
	_init_player(&(params->player));
	set_event(&(params->data), params);
	mlx_loop_hook(params->data.mlx, &main_loop, (void *)params);
	mlx_loop(params->data.mlx);
	return (0);
}
