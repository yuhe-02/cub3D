/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 03:48:15 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/02 16:58:49 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_params *_init_params()
{
	t_params *params;

	params = (t_params *)malloc(sizeof(t_params));
	if (!params) 
		error_exit("malloc error\n", 1);
	memset(params, 0, sizeof(t_params));
	params->data.tex_east.path = NULL;
	params->data.tex_west.path = NULL;
	params->data.tex_north.path = NULL;
	params->data.tex_south.path = NULL;
	params->data.ceilling_color = -1;
	params->data.floor_color = -1;
	params->player.init_userpos_x = -1;
	params->player.init_userpos_y = -1;
}