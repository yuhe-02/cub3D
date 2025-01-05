/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 03:48:15 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/05 16:11:21 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// TODO change map, map_width, map_height paramter into char **
void	init_params(t_params* params, t_data *data, t_ray *ray, t_player *player, char (*world_map)[mapWidth + 1])
{
	params->data = data;
	params->player = player;
	params->ray = ray;
	params->map = world_map;
	params->map_width = mapWidth;
	params->map_height = mapHeight;
}