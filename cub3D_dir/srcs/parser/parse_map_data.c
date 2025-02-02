#include "utils.h"

static void set_player_pos(t_ivec *pos, t_params *params, int dir_x, int dir_y)
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

static int process_map_line_content(char *map_line, int j, int line_len, t_params *params)
{
	t_ivec	pos;

	pos.x = 0;
	pos.y = j;
	while (pos.x < line_len)
	{
		if (map_line[pos.x] == ' ' || map_line[pos.x] == '\t')
			params->map[pos.y][pos.x] = ' ';
		else
			params->map[pos.y][pos.x] = map_line[pos.x];
		if (map_line[pos.x] == 'N')
			set_player_pos(&pos, params, 0, -1);
		else if (map_line[pos.x] == 'S')
			set_player_pos(&pos, params, 0, 1);
		else if (map_line[pos.x] == 'E')
			set_player_pos(&pos, params, 1, 0);
		else if (map_line[pos.x] == 'W')
			set_player_pos(&pos, params, -1, 0);
		(pos.x)++;
	}
	while (pos.x < params->map_width) 
	{
		params->map[pos.y][pos.x] = ' ';
		(pos.x)++;
	}
	params->map[pos.y][pos.x] = '\0';
	return (0);
}

static int process_map_line(char *map_line, int j, t_params *params)
{
	int line_len;
	int	k;

	line_len = ft_strlen(map_line);
	params->map[j] = malloc(params->map_width + 1);
	if (!params->map[j])
		error_exit("malloc failed for map[j]\n", 1);
	k = process_map_line_content(map_line, j, line_len, params);
	return (0);
}

static int calc_maxwidth(t_params *params, int start_index, char **line)
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

int _parse_map_data(char **line, int start_index, int line_count, t_params *params)
{
	int i;

	params->map_height = line_count - start_index;
	params->map = malloc(params->map_height * sizeof(char *));
	if (!params->map)
		error_exit("malloc failed for map\n", 1);
	params->map_width = calc_maxwidth(params, start_index, line);
	_fill_space(params->map_height, params->map_width, start_index, line);
	// for (int j = 0; line[start_index + j]; j++) {
	// 	printf("line: '%s'\n", line[start_index + j]);
	// }
	if (_check_valid_map(params->map_height, start_index, line))
		error_exit("Invalid map\n", 1);
	i = 0;
	while (i < params->map_height)
	{
		process_map_line(line[start_index + i], i, params);
		i++;
	}
	return (0);
}
