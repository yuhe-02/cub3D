#include "utils.h"

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
		error_exit("multi position set\n", 1);
	*tmp = ft_strtrim(line[i] + 3, "\n");
	return (1);
}

static int	_handle_floor_ceiling_color_(char **line, int i, t_params *params)
{
	int		*tmp;
	t_data	*data;
	char	*tmp_line;

	data = &(params->data);
	if (ft_strncmp(line[i], "F ", 2) == 0)
		tmp = &(data->floor_color);
	else if (ft_strncmp(line[i], "C ", 2) == 0)
		tmp = &(data->ceilling_color);
	else 
		return (0);
	if (*tmp != -1)
		error_exit("multi position set\n", 1);
	tmp_line = ft_strtrim(line[i] + 2, "\n \t");
	*tmp = parse_color(tmp_line);
	free(tmp_line);
	return (1);
}

static int	_handle_map_elements_(char **line, int i, t_params *params)
{
	int result;

	result = _handle_texture_(line, i, params);
	if (result == 1)
		return (1);
	result = _handle_floor_ceiling_color_(line, i, params);
	if (result == 1)
		return (1);
	return (0);
}

int	_parse_map_settings(char **line, int line_count, t_params *params)
{
	int i;
	int	result;

	i = 0;
	while (i < line_count)
	{
		result = _handle_map_elements_(line, i, params);
		if (result == 1)
			i++;
		else if (result == 0 && line[i][0] == '\0')
			i++;
		else
			break ;
	}
	return (i);
}
