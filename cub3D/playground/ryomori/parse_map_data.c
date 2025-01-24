#include "utils.h"
#include "libft.h"
#include "raycast.h"

//==============================================================
// parse_map_data : set_player_north
//==============================================================

void set_player_north(int k, int j, t_params *params)
{
	params->player->init_userdir_x = 0;
	params->player->init_userdir_y = -1;
	params->player->init_userpos_x = k;
	params->player->init_userpos_y = j;
	fprintf(stderr, "player->init_userpos_x = %d\n", params->player->init_userpos_x);
	fprintf(stderr, "player->init_userpos_y = %d\n", params->player->init_userpos_y);
	fprintf(stderr, "player->init_userdir_x = %d\n", params->player->init_userdir_x);
	fprintf(stderr, "player->init_userdir_y = %d\n", params->player->init_userdir_y);
}

void	set_player_south(int k, int j, t_params *params)
{
	params->player->init_userdir_x = 0;
	params->player->init_userdir_y = 1;
	params->player->init_userpos_x = k;
	params->player->init_userpos_y = j;
	fprintf(stderr, "player->init_userpos_x = %d\n", params->player->init_userpos_x);
	fprintf(stderr, "player->init_userpos_y = %d\n", params->player->init_userpos_y);
	fprintf(stderr, "player->init_userdir_x = %d\n", params->player->init_userdir_x);
	fprintf(stderr, "player->init_userdir_y = %d\n", params->player->init_userdir_y);
}

void	set_player_east(int k, int j, t_params *params)
{
	params->player->init_userdir_x = 1;
	params->player->init_userdir_y = 0;
	params->player->init_userpos_x = k;
	params->player->init_userpos_y = j;
	fprintf(stderr, "player->init_userpos_x = %d\n", params->player->init_userpos_x);
	fprintf(stderr, "player->init_userpos_y = %d\n", params->player->init_userpos_y);
	fprintf(stderr, "player->init_userdir_x = %d\n", params->player->init_userdir_x);
	fprintf(stderr, "player->init_userdir_y = %d\n", params->player->init_userdir_y);
}

void	set_player_west(int k, int j, t_params *params)
{
	params->player->init_userdir_x = -1;
	params->player->init_userdir_y = 0;
	params->player->init_userpos_x = k;
	params->player->init_userpos_y = j;
	fprintf(stderr, "player->init_userpos_x = %d\n", params->player->init_userpos_x);
	fprintf(stderr, "player->init_userpos_y = %d\n", params->player->init_userpos_y);
	fprintf(stderr, "player->init_userdir_x = %d\n", params->player->init_userdir_x);
	fprintf(stderr, "player->init_userdir_y = %d\n", params->player->init_userdir_y);
}

//==============================================================
// parse_map_settings : handle_map_elements
//==============================================================
int prosess_map_line_content(char *map_line, int j, int line_len, t_params *params)
{
	int k;

	k = 0;
	while (k < line_len)//※治してない：どれか一つでも条件に合致したら、その位置を記録する2つあったらエラー
	{
		params->map[j][k] = map_line[k];
		if (params->map[j][k] == 'N')
			set_player_north(k, j, params);
		else if (params->map[j][k] == 'S')
			set_player_south(k, j, params);
		else if (params->map[j][k] == 'E')
			set_player_east(k, j, params);
		else if (params->map[j][k] == 'W')
			set_player_west(k, j, params);
		k++;
	}
	return (0);
}

// //==============================================================
// // parse_map_data
// //==============================================================
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
	params->map[j] = malloc(line_len + 1);
	if (!params->map[j])
	{
		write(2, "malloc failed for map[j]\n", 26);
		return (-1);
	}
	k = prosess_map_line_content(map_line, j, line_len, params);
	params->map[j][line_len] = '\0';
	return (0);
}

int parse_map_data(char **line, int start_index, int line_count, t_params *params)
{
	int j;
	int tmp_start_index;

	tmp_start_index = start_index;//※治してない：start_index
	// マップ全体のメモリを確保
	if (allocate_map_memory(line, start_index, line_count, params) != 0)
		return (-1);
	// 各行を処理
	j = 0;
	while (j < params->map_height)
	{
		if (!line[start_index + j])
		{
			write(2, "Error : Map line is NULL\n", 25);
			return (-1);
		}
		if (process_map_line(line[start_index + j], j, params) != 0)
			return (-1);
		j++;
	}
	return (0);
}
