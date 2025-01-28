/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 03:48:15 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/28 13:27:06 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// TODO change map, map_width, map_height paramter into char **
t_params *_init_params(char (*world_map)[mapWidth + 1])
{
	t_params *params;

	params = (t_params *)malloc(sizeof(t_params));
	params->map2 = world_map;
	params->map_width = 0;
	params->map_height = 0;
}