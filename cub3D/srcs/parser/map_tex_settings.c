#include "utils.h"
#include "libft.h"
#include "raycast.h"

char *is_space(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (str + i);
}

void	remove_newline(char *str)
{
	char	*newline;
	newline = ft_strchr(str, '\n');
	if (newline)
		*newline = '\0';
}

//==============================================================
//parse_map_settings :handle_north_south_texture
//==============================================================

int	handle_texture(char **line, int i, t_params *params)
{
	char **tmp;
	if (ft_strncmp(line[i], "NO ", 3) == 0)
	{
		tmp = &(params->data->tex_north.path);
		// update flag
	} else if (ft_strncmp(line[i], "SO ", 3) == 0)
	{
		tmp = &(params->data->tex_south.path);
		// update flag
	} else if (ft_strncmp(line[i], "EA ", 3) == 0)
	{
		tmp = &(params->data->tex_east.path);
		// update flag
	} else if (ft_strncmp(line[i], "WE ", 3) == 0)
	{
		tmp = &(params->data->tex_west.path);
		// update flag
	} else {
		return (0);
	}
	line[i] = is_space(line[i]);
	*tmp = ft_strdup(line[i] + 3);
	remove_newline(*tmp);
	return (1);
}
//==============================================================
//parse_map_settings :handle_floor_ceiling_color
//==============================================================

int	handle_floor_ceiling_color(char **line, int i, t_params *params)
{
	int	*tmp;

	if (ft_strncmp(line[i], "F ", 2) == 0)
	{
		tmp = &(params->data->floor_color);
	}
	else if (ft_strncmp(line[i], "C ", 2) == 0)
	{
		tmp = &(params->data->ceilling_color);
	} else 
		return (0);
	line[i] = is_space(line[i]);
	if (parse_color(line[i] + 2, tmp) != 0)
	{
		write(2, "Error\nInvalid color\n", 20);
		return (-1);
	}
	return (1);
}

//==============================================================
//parse_map_settings :handle_map_elements
//==============================================================
int	handle_map_elements(char **line, int i, t_params *params)
{
	int result;

	result = handle_texture(line, i, params);
	if (result == 1)
		return (i + 1);
	result = handle_floor_ceiling_color(line, i, params);
	if (result == -1)
		return (-1);
	if (result == 1)
		return (i + 1);
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
		else if (result > 0)
			i = result;
		else if (result == 0 && (line[i][0] == '\n' && line[i][1] == '\0'))
			i++;
		else
			break;
		// 行の終了のこと?多分不要かも
	}
	return (i);
}
