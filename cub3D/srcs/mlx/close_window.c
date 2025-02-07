/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:48:11 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:48:49 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	free_maps(t_params *params)
{
	int	i;

	i = 0;
	while (0 < params->map_height)
	{
		free(params->map[i]);
		i++;
	}
	free(params->map);
}

// TODO 時間あったらなおす
int	_close_window(t_params *param)
{
	t_data	*data;

	data = &(param->data);
	if (!data)
		exit(0);
	if (data->img.img)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		data->img.img = NULL;
	}
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	exit(0);
	return (0);
}
