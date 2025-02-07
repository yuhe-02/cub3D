/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:13:22 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:33:31 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int	is_valid_ascii(char c)
{
	return (c == 'S' || c == 'W' || c == 'E' || c == 'N' || c == '\t'
		|| c == ' ' || c == '0' || c == '1');
}

int	is_space(int c)
{
	return (c == ' ' || c == '\t');
}

int	is_user_dir(char c)
{
	return (c == 'S' || c == 'W' || c == 'E' || c == 'N');
}

int	is_field(char c)
{
	return (c == '0' || c == '1');
}
