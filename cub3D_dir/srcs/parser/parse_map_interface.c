/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_interface.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:51:44 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/02 16:59:01 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	_parse_map(char **line, t_params *params)
{
	int start_index;
	
	start_index = _parse_map_settings(line, params);
	if (start_index < 0)
		return (-1);
	_parse_map_data(line, start_index, params);
	return (0);
}