/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:13:22 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:36:35 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static void	assign_char_(t_map_info *info, char **line, int len,
		int start_index)
{
	int	height;

	height = start_index + info->y;
	if (info->y == 0)
		info->above = 0;
	else
		info->above = line[height - 1][info->x];
	if (info->y == len - 1)
		info->bottom = 0;
	else
		info->bottom = line[height + 1][info->x];
	info->current = line[height][info->x];
	info->next = line[height][info->x + 1];
}

static int	_check_near_(t_map_info *info, int i, int len, int j)
{
	int	flg;
	int	flg_next;

	flg = (info->current == '0') || is_user_dir(info->current);
	flg_next = (info->next == '0') || is_user_dir(info->next);
	if (j == 0 && flg)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR1, ERR_EDGE));
	if (flg && (is_space(info->next) || !info->next))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR1, ERR_EMPTY));
	if (i == 0 && flg)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR1, ERR_EDGE));
	if (i == len - 1 && flg)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR1, ERR_EDGE));
	if (flg && is_space(info->above))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR1, ERR_EMPTY));
	if (flg && is_space(info->bottom))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR1, ERR_EMPTY));
	if (is_space(info->current) && flg_next)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR1, ERR_EMPTY));
	if (!is_valid_ascii(info->current))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR1, ERR_ASCII));
	return (0);
}

static int	is_empty_line_(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (!is_space(line[j]))
			return (0);
		j++;
	}
	return (1);
}

static int	_check_empty_line_(t_map_info *info, char **line, int len,
		int start_index)
{
	int	i;
	int	j;

	if (!is_empty_line_(line[start_index + info->y]))
		return (0);
	j = 0;
	i = info->y + 1;
	while (i < len)
	{
		j = 0;
		while (line[start_index + i][j])
		{
			if (is_user_dir(line[start_index + i][j])
				|| is_field(line[start_index + i][j]))
				return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR1,
						ERR_EMPTY_LINE));
			j++;
		}
		i++;
	}
	return (0);
}

int	_check_valid_map(int len, int start_index, char **line)
{
	t_map_info	info;

	info.y = 0;
	while (info.y < len)
	{
		info.x = 0;
		if (_check_empty_line_(&info, line, len, start_index))
			return (1);
		while (line[start_index + info.y][info.x])
		{
			assign_char_(&info, line, len, start_index);
			if (_check_near_(&info, info.y, len, info.x))
				return (1);
			(info.x)++;
		}
		(info.y)++;
	}
	return (0);
}
