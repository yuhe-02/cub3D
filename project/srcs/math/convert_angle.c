/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_angle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 07:01:51 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/03 14:22:09 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

double	convert_to_radian(int degree)
{	
	double	res;

	res = (double)((double)degree / 180 * PI);
	return (res);
}

int		convert_to_degree(double radian)
{
	int	res;

	res = (int)(radian * 180 / PI);
	return (res);
}