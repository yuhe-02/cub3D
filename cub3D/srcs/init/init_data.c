/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 03:52:00 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/01 03:53:42 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_data(t_data *data)
{
	data->width = WIDTH;
	data->height = HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "Raycaster sample");
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img, &(data->bpp), &(data->llen),
			&(data->eda));
}