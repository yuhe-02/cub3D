/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:02:04 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/30 14:15:28 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// TODO プレイヤーの向いている方向に対して移動しないといけないから修正
// TODO 移動するピクセル数がよくわからんので調整
// TODO 横の壁にぶつかったとき不自然すぎる
// TODO 回転幅の調整等
static int	move_by_key(int keycode, t_params *param)
{
	t_player *player;
	double move_speed = 0.5; // 移動速度（調整可能）

	player = param->player;

	if (keycode == KEY_W)
	{
		double next_x = player->pos_x + player->dir_x * move_speed;
		double next_y = player->pos_y + player->dir_y * move_speed;
		if (param->map[(int)next_x][(int)player->pos_y] == 0)
			player->pos_x = next_x;
		if (param->map[(int)player->pos_x][(int)next_y] == 0)
			player->pos_y = next_y;

		printf("move forward (x, y)=(%f, %f)\n", player->pos_x, player->pos_y);
	}

	if (keycode == KEY_S)
	{
		double next_x = player->pos_x - player->dir_x * move_speed;
		double next_y = player->pos_y - player->dir_y * move_speed;
		if (param->map[(int)next_x][(int)player->pos_y] == 0)
			player->pos_x = next_x;
		if (param->map[(int)player->pos_x][(int)next_y] == 0)
			player->pos_y = next_y;

		printf("move back (x, y)=(%f, %f)\n", player->pos_x, player->pos_y);
	}

	if (keycode == KEY_A)
	{
		double next_x = player->pos_x - player->plane_x * move_speed;
		double next_y = player->pos_y - player->plane_y * move_speed;
		if (param->map[(int)next_x][(int)player->pos_y] == 0)
			player->pos_x = next_x;
		if (param->map[(int)player->pos_x][(int)next_y] == 0)
			player->pos_y = next_y;

		printf("move left (x, y)=(%f, %f)\n", player->pos_x, player->pos_y);
	}
	if (keycode == KEY_D)
	{
		double next_x = player->pos_x + player->plane_x * move_speed;
		double next_y = player->pos_y + player->plane_y * move_speed;
		if (param->map[(int)next_x][(int)player->pos_y] == 0)
			player->pos_x = next_x;
		if (param->map[(int)player->pos_x][(int)next_y] == 0)
			player->pos_y = next_y;

		printf("move right (x, y)=(%f, %f)\n", player->pos_x, player->pos_y);
	}

	if (keycode == KEY_R_DIR)
	{
		double rot_speed = 0.05;
		double old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-rot_speed) - player->dir_y * sin(-rot_speed);
		player->dir_y = old_dir_x * sin(-rot_speed) + player->dir_y * cos(-rot_speed);

		double old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-rot_speed) - player->plane_y * sin(-rot_speed);
		player->plane_y = old_plane_x * sin(-rot_speed) + player->plane_y * cos(-rot_speed);

		printf("turn right direction\n");
	}

	if (keycode == KEY_L_DIR)
	{
		double rot_speed = 0.05;
		double old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
		player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);

		double old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y * sin(rot_speed);
		player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y * cos(rot_speed);
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