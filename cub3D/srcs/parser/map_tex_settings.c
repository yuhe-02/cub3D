#include "utils.h"
#include "libft.h"
#include "raycast.h"

//==============================================================
//parse_map_settings :handle_north_south_texture
//==============================================================

int	handle_texture(char **line, int i, t_params *params)
{
	char	**tmp;
	t_data	*data;

	data = &(params->data);
	if (ft_strncmp(line[i], "NO ", 3) == 0)
	{
		tmp = &(data->tex_north.path);
		// update flag
	} else if (ft_strncmp(line[i], "SO ", 3) == 0)
	{
		tmp = &(data->tex_south.path);
		// update flag
	} else if (ft_strncmp(line[i], "EA ", 3) == 0)
	{
		tmp = &(data->tex_east.path);
		// update flag
	} else if (ft_strncmp(line[i], "WE ", 3) == 0)
	{
		tmp = &(data->tex_west.path);
		// update flag
	} else 
	{
		return (0);
	}
	*tmp = ft_strtrim(line[i] + 3, "\n");
	return (1);
}

int	handle_floor_ceiling_color(char **line, int i, t_params *params)
{
	int		*tmp;
	t_data	*data;
	char	*tmp_line;

	data = &(params->data);
	if (ft_strncmp(line[i], "F ", 2) == 0)
	{
		tmp = &(data->floor_color);
	}
	else if (ft_strncmp(line[i], "C ", 2) == 0)
	{
		tmp = &(data->ceilling_color);
	} 
	else 
		return (0);
	tmp_line = ft_strtrim(line[i] + 2, "\n \t");
	if (parse_color(tmp_line, tmp) != 0)
	{
		write(2, "Error\nInvalid color\n", 20);
		exit(1);
	}
	free(tmp_line);
	return (1);
}

int	handle_map_elements(char **line, int i, t_params *params)
{
	int result;

	result = handle_texture(line, i, params);
	if (result == 1)
		return (i + 1);
	result = handle_floor_ceiling_color(line, i, params);
	if (result == 1)
		return (i + 1);
	return (0);
}

int	parse_map_settings(char **line, int line_count, t_params *params)
{
	int i;
	int	result;

	i = 0;
	while (i < line_count)
	{
		result = handle_map_elements(line, i, params);
		if (result > 0)
			i = result;
		else if (result == 0 && (line[i][0] == '\n' && line[i][1] == '\0'))
			i++;
		// else
		// 	break;
		// // 行の終了のこと?多分不要かも
	}
	return (i);
}
