/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:51:44 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/28 15:02:59 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	_parse_map(char **line, int line_count, t_params *params)
{
	int start_index;
	
	start_index = _parse_map_settings(line, line_count, params);
	if (start_index < 0)
		return (-1);
	_parse_map_data(line, start_index, line_count, params);
	return (0);
}