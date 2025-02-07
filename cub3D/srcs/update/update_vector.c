/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:31:03 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:31:23 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	_vector_assign(t_vector *vector, double new_x, double new_y)
{
	vector->x = new_x;
	vector->y = new_y;
}
