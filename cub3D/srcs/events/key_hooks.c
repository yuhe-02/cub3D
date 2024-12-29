/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:02:04 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/24 13:19:20 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	move_by_key(int keycode, t_params *param)
{
	if (keycode == KEY_W)
	{
		printf("move forward\n");
	}
	if (keycode == KEY_S)
	{
		printf("move back\n");
	}
	if (keycode == KEY_A)
	{
		printf("move left\n");
	}
	if (keycode == KEY_D)
	{
		printf("move right\n");
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

int	key_hook(int keycode, void *data)
{
	t_params	*param;

	param = (t_params *)data;
	if (keycode == KEY_ESC)
		close_window(param);
	else if (keycode == KEY_W || keycode == KEY_S
		|| keycode == KEY_A || keycode == KEY_D
		|| keycode == KEY_R_DIR || keycode == KEY_L_DIR)
		move_by_key(keycode, param);
	else
		return (0);
	// ft_bzero(param->data.addr, param->data.llen * HEIGHT);
	return (0);
}