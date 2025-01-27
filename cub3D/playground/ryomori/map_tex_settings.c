#include "utils.h"
#include "libft.h"
#include "raycast.h"


//==============================================================
//parse_map_settings :handle_north_south_texture
//==============================================================

int	handle_no_so_texture(char **line, int i, t_params *params)
{
	if (ft_strncmp(line[i], "NO ", 3) == 0)
	{
		line[i] = is_spase(line[i]);
		params->data->tex_north.addr = ft_strdup(line[i] + 3);
		remove_newline(params->data->tex_north.addr);
		return (1);
	}
	else if (ft_strncmp(line[i], "SO ", 3) == 0)
	{
		line[i] = is_spase(line[i]);
		params->data->tex_south.addr = ft_strdup(line[i] + 3);
		remove_newline(params->data->tex_south.addr);
		return (1);
	}
	return (0);
}
//==============================================================
//parse_map_settings :handle_east_west_texture
//==============================================================

int	handle_ea_we_texture(char **line, int i, t_params *params)
{
	if (ft_strncmp(line[i], "EA ", 3) == 0)
	{
		line[i] = is_spase(line[i]);
		params->data->tex_east.addr = ft_strdup(line[i] + 3);
		remove_newline(params->data->tex_east.addr);
		return (1);
	}
	else if (ft_strncmp(line[i], "WE ", 3) == 0)
	{
		line[i] = is_spase(line[i]);
		params->data->tex_west.addr = ft_strdup(line[i] + 3);
		remove_newline(params->data->tex_west.addr);
		return (1);
	}
	return (0);
}
//==============================================================
//parse_map_settings :handle_floor_ceiling_color
//==============================================================

int	handle_floor_ceiling_color(char **line, int i, t_params *params)
{
	if (ft_strncmp(line[i], "F ", 2) == 0)
	{
		line[i] = is_spase(line[i]);
		if (parse_color(line[i] + 2, &params->data->floor_color) != 0)
		{
			write(2, "Error\nInvalid floor color\n", 27);
			return (-1);
		}
		return (1);
	}
	else if (ft_strncmp(line[i], "C ", 2) == 0)
	{
		line[i] = is_spase(line[i]);
		if (parse_color(line[i] + 2, &params->data->ceilling_color) != 0)
		{
			write(2, "Error\nInvalid ceilling color\n", 30);
			return (-1);
		}
		return (1);
	}
	return (0);
}

//==============================================================
//parse_map_settings :handle_map_elements
//==============================================================
int	handle_map_elements(char **line, int i, t_params *params)
{
	int result;

	result = handle_no_so_texture(line, i, params);
	if (result == 1)
	{
		i++;
		return (i);
	}
	result = handle_ea_we_texture(line, i, params);
	if (result == 1)
	{
		i++;
		return (i);
	}
	result = handle_floor_ceiling_color(line, i, params);
	if (result == -1)
		return (-1);
	if (result == 1)
	{
		i++;
		return (i);
	}
	return (0);
}

//==============================================================
//parse_map_settings
//==============================================================

int	parse_map_settings(char **line, int line_count, t_params *params)
{
	int i;
	int	result;

	i = 0;
	while (i < line_count)
	{
		result = handle_map_elements(line, i, params);
		if (result == -1)
			return (-1);
		if (result > 0)
		{
			i = result;
			continue;
		}
		if (line[i][0] == '\n' && line[i][1] == '\0')
		{
			fprintf(stderr, "spase line\n");
			i++;
			continue;
		}
		break;
	}
	return (i);
}
