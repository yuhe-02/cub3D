/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:02:04 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/30 15:41:08 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// TODO プレイヤーの向いている方向に対して移動しないといけないから修正
// TODO 移動するピクセル数がよくわからんので調整
// TODO 横の壁にぶつかったとき不自然すぎる
// TODO 回転幅の調整等
// TODO 一回転するとセグフォする
static int	move_by_key(int keycode, t_params *param)
{
	t_player *player;
	double move_speed = 0.5; // 移動速度（調整可能）

	player = param->player;

	if (keycode == KEY_W)
		player->vertical_flag = 1;
	if (keycode == KEY_S)
		player->vertical_flag = -1;
	if (keycode == KEY_A)
		player->horizontal_flag = -1;
	if (keycode == KEY_D)
		player->horizontal_flag = 1;
	if (keycode == KEY_R_DIR)
		player->counterclockwise_flag = -1;
	if (keycode == KEY_L_DIR)
		player->counterclockwise_flag = 1;
	return (0);
}

int	key_hook(int keycode, void *arg)
{
	t_data	*data;
	t_params *params;

	params = (t_params *)arg;
	data = (t_data *)(params->data);
	if (keycode == KEY_ESC)
		close_window(params);
	else if (keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_A || keycode == KEY_D
		|| keycode == KEY_R_DIR || keycode == KEY_L_DIR)
		move_by_key(keycode, params);
	else
		return (0);
	ft_bzero(data->addr, data->llen * data->height);
	return (0);
}