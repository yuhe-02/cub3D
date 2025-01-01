/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:01:56 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/30 11:50:16 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// TODO 時間あったらなおす
int	close_window(t_params *param)
{
	t_data	*data;

	data = param->data;
	if (!data)
		exit(0);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	// if (data->mlx)
	// {
	// 	// mlx_destroy_display(data->mlx);
	// 	// free(data->mlx);
	// 	// data->mlx = NULL;
	// }
	exit(0);
	return (0);
}