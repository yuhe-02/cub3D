/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:02:04 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/30 12:54:59 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// TODO プレイヤーの向いている方向に対して移動しないといけないから修正
static int	move_by_key(int keycode, t_params *param)
{
	t_player *player;

	player = param->player;
	if (keycode == KEY_W)
	{
		player->pos_y -= 1;
		printf("move forward (x, y)=(%f, %f)\n", player->pos_x, player->pos_y);
	}
	if (keycode == KEY_S)
	{
		player->pos_y += 1;
		printf("move back (x, y)=(%f, %f)\n", player->pos_x, player->pos_y);
	}
	if (keycode == KEY_A)
	{
		player->pos_x -= 1;
		printf("move left (x, y)=(%f, %f)\n", player->pos_x, player->pos_y);
	}
	if (keycode == KEY_D)
	{
		player->pos_x += 1;
		printf("move right (x, y)=(%f, %f)\n", player->pos_x, player->pos_y);
	}
	if (keycode == KEY_R_DIR)
	{
		printf("turn right direction\n");
	}
	if (keycode == KEY_L_DIR)
	{
		printf("turn left direction\n");
	}
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