/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:34:17 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:36:19 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static int	_fill_space_(int width, int start_index, char **line)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (line[start_index + i])
	{
		tmp = (char *)malloc(sizeof(char) * (width + 1));
		if (!tmp)
			return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR3, ERR_ALLOC));
		j = 0;
		while (line[start_index + i][j])
		{
			tmp[j] = line[start_index + i][j];
			j++;
		}
		while (j < width)
			tmp[j++] = ' ';
		tmp[j] = '\0';
		free(line[start_index + i]);
		line[start_index + i] = tmp;
		i++;
	}
	return (0);
}

static int	_set_player_pos_(t_ivec *pos, t_params *params, int dir_x,
		int dir_y)
{
	t_player	*player;

	player = &(params->player);
	player->init_userdir_x = dir_x;
	player->init_userdir_y = dir_y;
	if (player->init_userpos_x != -1)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_DUBPAR));
	player->init_userpos_x = pos->x;
	player->init_userpos_y = pos->y;
	return (0);
}

static int	_process_map_line_(char *map_line, int j, t_params *params)
{
	t_ivec	pos;
	int		err;

	params->map[j] = ft_strdup(map_line);
	if (!params->map[j])
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR3, ERR_ALLOC));
	pos.x = 0;
	pos.y = j;
	err = 0;
	while (pos.x < params->map_width)
	{
		if (map_line[pos.x] == 'N')
			err = _set_player_pos_(&pos, params, 0, -1);
		else if (map_line[pos.x] == 'S')
			err = _set_player_pos_(&pos, params, 0, 1);
		else if (map_line[pos.x] == 'E')
			err = _set_player_pos_(&pos, params, 1, 0);
		else if (map_line[pos.x] == 'W')
			err = _set_player_pos_(&pos, params, -1, 0);
		if (err)
			return (1);
		(pos.x)++;
	}
	return (0);
}

int	_parse_map_data(char **line, int start_index, t_params *params)
{
	int	i;

	params->map_height = count_map_height(start_index, line);
	params->map = malloc(params->map_height * sizeof(char *));
	if (!params->map)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR3, ERR_ALLOC));
	params->map_width = calc_max_width(params, start_index, line);
	if (_fill_space_(params->map_width, start_index, line))
		return (1);
	if (_check_valid_map(params->map_height, start_index, line))
		return (1);
	i = 0;
	while (i < params->map_height)
	{
		if (_process_map_line_(line[start_index + i], i, params))
			return (1);
		i++;
	}
	return (0);
}
