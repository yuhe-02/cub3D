/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:40:41 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:54:48 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	error_exit(const char *str, int error_num)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	exit(error_num);
}
