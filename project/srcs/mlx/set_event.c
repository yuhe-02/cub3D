/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:49:37 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:49:41 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	set_event(t_data *data, t_params *params)
{
	mlx_hook(data->win, 17, 0, _close_window, params);
	mlx_hook(data->win, KeyPress, KeyPressMask, _key_hook, params);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, _key_release_hook, params);
}
