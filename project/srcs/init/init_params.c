/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 03:48:15 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:51:56 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int	_init_params(t_params **params)
{
	(*params) = (t_params *)malloc(sizeof(t_params));
	if (!(*params))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR3, ERR_ALLOC));
	memset((*params), 0, sizeof(t_params));
	(*params)->data.tex_east.path = NULL;
	(*params)->data.tex_west.path = NULL;
	(*params)->data.tex_north.path = NULL;
	(*params)->data.tex_south.path = NULL;
	(*params)->data.ceilling_color = -1;
	(*params)->data.floor_color = -1;
	(*params)->player.init_userpos_x = -1;
	(*params)->player.init_userpos_y = -1;
	return (0);
}
