#include "utils.h"

static void set_player_pos(t_ivec *pos, t_params *params, int dir_x, int dir_y)
{
	t_player *player;

	player = &(params->player);
	player->init_userdir_x = dir_x;
	player->init_userdir_y = dir_y;
	if (player->init_userpos_x != -1)
	{
		write(1, "multi set\n", ft_strlen("multi set\n"));
		exit(1);
	}
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
	{
		write(2, "malloc failed for map[j]\n", 26);
		return (-1);
	}
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

static int check_valid_map_(int len, int start_index, char **line)
{
	int	i;
	int	j;

	i = 0;
	// TODO if 入力予期していないアスキーの場合の処理
	// TODO if ユーザーの位置が存在しない、または複数候補があるとき
	// TODO if 壁で囲まれていない場合
	while (i < len)
	{
		j = 0;
		while (line[start_index + i][j])
		{
			if (!ft_strchr("SWEN \t01", line[start_index + i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);

}

int _parse_map_data(char **line, int start_index, int line_count, t_params *params)
{
	int i;

	params->map_height = line_count - start_index;
	params->map = malloc(params->map_height * sizeof(char *));
	if (!params->map)
	{
		write(2, "malloc failed for map\n", 23);
		exit(1);
	}
	if (check_valid_map_(params->map_height, start_index, line))
	{
		write(1, "Invalid map\n", 12);
		exit(1);
	}
	params->map_width = calc_maxwidth(params, start_index, line);
	i = 0;
	while (i < params->map_height)
	{
		process_map_line(line[start_index + i], i, params);
		i++;
	}
	return (0);
}
