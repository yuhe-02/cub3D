#include "utils.h"
#include "libft.h"
#include "raycast.h"

//==============================================================
// parse_map_data : set_player_north
//==============================================================

static void set_player_pos(t_ivec *pos, t_params *params, int dir_x, int dir_y)
{
	params->player->init_userdir_x = dir_x;
	params->player->init_userdir_y = dir_y;
	params->player->init_userpos_x = pos->x;
	params->player->init_userpos_y = pos->y;
	printf("%d %d\n", pos->x, pos->y);
}

//==============================================================
// parse_map_settings : handle_map_elements
//==============================================================
int process_map_line_content(char *map_line, int j, int line_len, t_params *params)
{
	t_ivec	pos;

	pos.x = 0;
	pos.y = j;
	// TODO if found unmatch patter
	// TODO if same condition matched
	// TODO if direction not found
	while (pos.x < line_len)
	{
		remove_newline(map_line);
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

int allocate_map_memory(char **line, int start_index, int line_count, t_params *params)
{
	params->map_height = line_count - start_index;
	params->map = malloc(params->map_height * sizeof(char *));
	if (!params->map)
	{
		write(2, "malloc failed for map\n", 23);
		return (-1);
	}
	return (0);
}


//==============================================================
// parse_map_data : process_map_line
//==============================================================

int process_map_line(char *map_line, int j, t_params *params)
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

int calc_maxwidth(t_params *params, int start_index, char **line)
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

int parse_map_data(char **line, int start_index, int line_count, t_params *params)
{
	int j;

	// マップ全体のメモリを確保
	if (allocate_map_memory(line, start_index, line_count, params) != 0)
		return (-1);
	// 各行を処理
	params->map_width = calc_maxwidth(params, start_index, line);
	j = 0;
	while (j < params->map_height)
	{
		if (!line[start_index + j])
		{
			params->map[j] = NULL;
			write(2, "Error : Map line is NULL\n", 25);
			return (-1);
		}
		if (process_map_line(line[start_index + j], j, params) != 0)
			return (-1);
		j++;
	}
	return (0);
}
