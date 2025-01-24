/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 04:14:10 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/24 14:24:13 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// TODO change position, direction, plane parameter based on arguments
void	init_player(t_player *player, int x, int y)
{
	player->pos_x = (double)x - 0.5;
	player->pos_y = (double)y - 0.5;
	player->dir_x = 0.0;
	player->dir_y = -1.0;
	player->plane_x = 0.66;
	player->plane_y = 0;
	player->side_flg = 0;
	player->approx_flg = 0;
	player->rotate_flg = 0;
}