/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 03:48:15 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/29 13:44:59 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// TODO change map, map_width, map_height paramter into char **
t_params *_init_params()
{
	t_params *params;

	params = (t_params *)malloc(sizeof(t_params));
	if (!params) {
		write(1, "malloc error\n", 13);
		exit(1);
	}
	memset(params, 0, sizeof(t_params ));
}