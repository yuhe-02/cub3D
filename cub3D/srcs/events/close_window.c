/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:01:56 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/24 13:29:30 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// TODO 時間あったらなおす
int	close_window(t_params *param)
{
	if (!param)
		exit(0);
	if (param->data.img)
		mlx_destroy_image(param->mlx, param->data.img);
	if (param->win)
		mlx_destroy_window(param->mlx, param->win);
	// if (param->mlx)
	// {
	// 	// mlx_destroy_display(param->mlx);
	// 	// free(param->mlx);
	// 	// param->mlx = NULL;
	// }
	exit(0);
	return (0);
}