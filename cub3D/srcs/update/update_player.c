/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:30:42 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:32:56 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

// TODO なんでこの実装にしたのか（plane計算部分）を調査する
static void	_update_player_dir_(t_player *player)
{
	t_vector	old_dir;
	t_vector	old_plane;
	t_vector	tmp;
	double		rotate_radian;

	old_dir.x = player->dir.x;
	old_dir.y = player->dir.y;
	old_plane.x = player->plane.x;
	old_plane.y = player->plane.y;
	rotate_radian = player->rotate_flg * ROT_SPEED;
	tmp.x = cos(rotate_radian);
	tmp.y = sin(rotate_radian);
	player->dir.x = old_dir.x * tmp.x - old_dir.y * tmp.y;
	player->dir.y = old_dir.x * tmp.y + old_dir.y * tmp.x;
	player->plane.x = old_plane.x * tmp.x - old_plane.y * tmp.y;
	player->plane.y = old_plane.x * tmp.y + old_plane.y * tmp.x;
}

static void	_update_player_pos_(t_params *param, t_player *player)
{
	t_vector	next;
	t_vector	tmp;

	if (player->side_flg != 0)
	{
		tmp.x = player->side_flg * player->plane.x * MOVE_SPEED;
		tmp.y = player->side_flg * player->plane.y * MOVE_SPEED;
	}
	else if (player->approx_flg != 0)
	{
		tmp.x = player->approx_flg * player->dir.x * MOVE_SPEED;
		tmp.y = player->approx_flg * player->dir.y * MOVE_SPEED;
	}
	next.x = player->pos.x + tmp.x;
	next.y = player->pos.y + tmp.y;
	if (param->map[(int)player->pos.y][(int)next.x] != '1')
		player->pos.x = next.x;
	if (param->map[(int)next.y][(int)player->pos.x] != '1')
		player->pos.y = next.y;
}

void	_update_player(t_params *param, t_player *player)
{
	if (player->rotate_flg != 0)
		_update_player_dir_(player);
	else if (player->side_flg != 0 || player->approx_flg != 0)
		_update_player_pos_(param, player);
}
