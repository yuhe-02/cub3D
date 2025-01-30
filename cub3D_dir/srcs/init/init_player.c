/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 04:14:10 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/30 14:07:47 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void		_init_player_dir_(t_player *player)
{

	if (player->init_userdir_y != 0)
	{
		player->dir.x = 0;
		player->dir.y = player->init_userdir_y;
		player->plane.x = (-1 * player->init_userdir_y) * tan(convert_to_radian(33));
		player->plane.y = 0;
	}
	else
	{
		player->dir.x = player->init_userdir_x;
		player->dir.y = 0;
		player->plane.x = 0;
		player->plane.y = (player->init_userdir_x) * tan(convert_to_radian(33));
	}
}

void	_init_player(t_player *player)
{
	player->pos.x = (double)player->init_userpos_x + 0.5;
	player->pos.y = (double)player->init_userpos_y + 0.5;
	_init_player_dir_(player);
	printf("%d %d\n", player->init_userdir_x, player->init_userdir_y);
	player->side_flg = 0;
	player->approx_flg = 0;
	player->rotate_flg = 0;
}