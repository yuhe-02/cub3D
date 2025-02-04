/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_settings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:36:58 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:36:58 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static int	_handle_texture_(char **line, int i, t_params *params)
{
	char	**tmp;
	t_data	*data;

	data = &(params->data);
	if (ft_strncmp(line[i], "NO ", 3) == 0)
		tmp = &(data->tex_north.path);
	else if (ft_strncmp(line[i], "SO ", 3) == 0)
		tmp = &(data->tex_south.path);
	else if (ft_strncmp(line[i], "EA ", 3) == 0)
		tmp = &(data->tex_east.path);
	else if (ft_strncmp(line[i], "WE ", 3) == 0)
		tmp = &(data->tex_west.path);
	else
		return (0);
	if (*tmp)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_DUBTEX));
	*tmp = ft_strtrim(line[i] + 3, "\n");
	return (-1);
}

static int	_handle_floor_ceiling_color_(char **line, int i, t_params *params)
{
	int		*tmp;
	t_data	*data;
	char	*tmp_line;
	int		err;

	data = &(params->data);
	if (ft_strncmp(line[i], "F ", 2) == 0)
		tmp = &(data->floor_color);
	else if (ft_strncmp(line[i], "C ", 2) == 0)
		tmp = &(data->ceilling_color);
	else
		return (0);
	if (*tmp != -1)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_DUBPAR));
	tmp_line = ft_strtrim(line[i] + 2, "\n \t");
	err = parse_color(tmp_line, tmp);
	free(tmp_line);
	if (err)
		return (1);
	return (-1);
}

static int	_handle_map_elements_(char **line, int i, t_params *params)
{
	int	err;

	err = _handle_texture_(line, i, params);
	if (err == -1)
		return (1);
	else if (err)
		return (-1);
	err = _handle_floor_ceiling_color_(line, i, params);
	if (err == -1)
		return (1);
	else if (err)
		return (-1);
	return (0);
}

int	_parse_map_settings(char **line, t_params *params)
{
	int	i;
	int	err;

	i = 0;
	while (line[i])
	{
		err = _handle_map_elements_(line, i, params);
		if (err == 1 || (err == 0 && line[i][0] == '\0'))
			i++;
		else if (err == -1)
			return (-1);
		else
			break ;
	}
	return (i);
}
