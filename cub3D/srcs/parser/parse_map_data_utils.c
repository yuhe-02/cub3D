/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_data_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:34:56 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:36:49 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int	calc_max_width(t_params *params, int start_index, char **line)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (j < params->map_height)
	{
		if ((int)(ft_strlen(line[j + start_index])) > len)
			len = ft_strlen(line[j + start_index]);
		j++;
	}
	return (len);
}

int	count_map_height(int start_index, char **line)
{
	int	i;

	i = 0;
	while (line[start_index + i])
		i++;
	return (i);
}
