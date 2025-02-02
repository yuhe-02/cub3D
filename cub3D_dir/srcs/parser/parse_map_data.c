#include "utils.h"

static void	_fill_space_(int height, int width, int start_index, char **line)
{
	int		i;
	int		j;
	int		end;
	char	*tmp;

	i = 0;
	while (i < height)
	{
		tmp = (char *)malloc(sizeof(char) * (width + 1));
		if (!tmp)
			error_exit("malloc failed", 1);
		j = 0;
		while (line[start_index + i][j])
		{
			tmp[j] = line[start_index + i][j];
			j++;
		}
		while (j < width)
		{
			tmp[j++] = ' ';
		}
		tmp[j] = '\0';
		free(line[start_index + i]);
		line[start_index + i] = tmp;
		i++;
	}
}

static void _set_player_pos_(t_ivec *pos, t_params *params, int dir_x, int dir_y)
{
	t_player *player;

	player = &(params->player);
	player->init_userdir_x = dir_x;
	player->init_userdir_y = dir_y;
	if (player->init_userpos_x != -1)
		error_exit("multi set\n", 1);
	player->init_userpos_x = pos->x;
	player->init_userpos_y = pos->y;
}

static int _process_map_line_(char *map_line, int j, t_params *params)
{
	t_ivec	pos;

	params->map[j] = ft_strdup(map_line);
	if (!params->map[j])
		error_exit("malloc failed for map[j]\n", 1);
	pos.x = 0;
	pos.y = j;
	while (pos.x < params->map_width)
	{		
		if (map_line[pos.x] == 'N')
			_set_player_pos_(&pos, params, 0, -1);
		else if (map_line[pos.x] == 'S')
			_set_player_pos_(&pos, params, 0, 1);
		else if (map_line[pos.x] == 'E')
			_set_player_pos_(&pos, params, 1, 0);
		else if (map_line[pos.x] == 'W')
			_set_player_pos_(&pos, params, -1, 0);
		(pos.x)++;
	}
	return (0);
}

static int calc_max_width_(t_params *params, int start_index, char **line)
{
	int j;
	int len;

	j = 0;
	len = 0;
	while (j < params->map_height)
	{
		if (ft_strlen(line[j+start_index]) > len)
			len = ft_strlen(line[j+start_index]);
		j++;
	}
	return (len);
}

static int	count_map_height_(int start_index, char **line)
{
	int	i;
	
	i = 0;
	while (line[start_index + i])
		i++;
	return (i);
}

int _parse_map_data(char **line, int start_index, t_params *params)
{
	int i;

	params->map_height = count_map_height_(start_index, line);
	params->map = malloc(params->map_height * sizeof(char *));
	if (!params->map)
		error_exit("malloc failed for map\n", 1);
	params->map_width = calc_max_width_(params, start_index, line);
	_fill_space_(params->map_height, params->map_width, start_index, line);
	// for (int j = 0; line[start_index + j]; j++) {
	// 	printf("line: '%s'\n", line[start_index + j]);
	// }
	if (_check_valid_map(params->map_height, start_index, line))
		error_exit("Invalid map\n", 1);
	i = 0;
	while (i < params->map_height)
	{
		_process_map_line_(line[start_index + i], i, params);
		i++;
	}
	return (0);
}
