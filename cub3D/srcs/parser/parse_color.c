/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 00:43:43 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 00:45:59 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static int	convert_rgb_hex(int *rgb_colors)
{
	int	hex_color;
	int	i;

	i = 0;
	hex_color = 0;
	while (i < 3)
	{
		hex_color = hex_color * 256 + rgb_colors[i];
		i++;
	}
	return (hex_color);
}

static int	parse_rgb_values(char **rgb, int *rgb_colors)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		rgb_colors[i] = ft_atoi(rgb[i]);
		if (!(rgb_colors[i] >= 0 && rgb_colors[i] <= 255))
			return (1);
		i++;
	}
	return (0);
}

static void	free_char_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i] != NULL)
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
}

int	check_parsed_value_(char **tmp)
{
	int	i;
	int	j;

	i = 0;
	while (tmp[i])
		i++;
	if (i != 3)
		return (1);
	while (i--)
	{
		if (!*tmp[i])
			return (1);
		j = 0;
		while (tmp[i][j])
		{
			if (!ft_isdigit(tmp[i][j]))
				return (1);
			j++;
		}
	}
	return (0);
}

int	parse_color(char *line, int *color)
{
	char	**rgb;
	int		rgb_color[3];

	rgb = ft_split(line, ',');
	if (!rgb)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR3, ERR_ALLOC));
	if (check_parsed_value_(rgb) || parse_rgb_values(rgb, rgb_color))
	{
		free_char_rgb(rgb);
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOCOLORFORM));
	}
	free_char_rgb(rgb);
	*color = convert_rgb_hex(rgb_color);
	return (0);
}
