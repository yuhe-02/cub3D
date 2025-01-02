/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:01:56 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/01 05:50:20 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_maps(t_params *params)
{
	int i;

	i = 0;
	while (0 < params->map_height)
	{
		free(params->map[i]);
		i++;
	}
	free(params->map);
}

// TODO 時間あったらなおす
int	close_window(t_params *param)
{
	t_data	*data;

	data = param->data;
	if (!data)
		exit(0);
	if (data->img)
	{
		mlx_destroy_image(data->mlx, data->img);
		data->img = NULL;
	}
	if (data->win)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	// if (param)
	// 	free_maps(param);
	if (data->mlx)
	{
		// mlx_destroy_display((void *)(data->mlx));
		// free(data->mlx);
		// data->mlx = NULL;
	}
	// exit(0);
	return (0);
}