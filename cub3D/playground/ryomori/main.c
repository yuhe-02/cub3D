
#include "utils.h"
#include "libft.h"
#include "raycast.h"

//==============================================================
// utils_fanctions
//==============================================================

char *is_spase(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (str + i);
}

void	remove_newline(char *str)
{
	char	*newline = strchr(str, '\n');
	if (newline)
		*newline = '\0';
}




int parse_map(char **line, int line_count, t_params *params)
{
	int start_index = parse_map_settings(line, line_count, params);
	if (start_index < 0)
		return (-1);
	parse_map_data(line, start_index, line_count, params);
	return (0);
}


//==============================================================
// read_functions
//==============================================================

char **read_map(const char *map_file, int *line_count)
{

	char		**line;
	int			fd;
	char		*cur_line;

	line = malloc(MAX_LINES * sizeof(char *));
	if (!line)
	{
		perror("malloc");
		return (NULL);
	}

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		perror("Faild to open file");
		free (line);
		return (NULL);
	}

	while ((cur_line = get_next_line(fd)) != NULL && *line_count < MAX_LINES)
	{
		line[*line_count] = cur_line;
		(*line_count)++;//行数をカウント
	}

	if (*line_count >= MAX_LINES)
		write (2, "Max line reached\n", 17);

	close(fd);
	return (line);
}

//==============================================================
// free_functions
//==============================================================

void	free_params(t_params *params)
{
	int i;

	i = 0;
	if (params->data->tex_north.addr)
		free(params->data->tex_north.addr);
	if (params->data->tex_south.addr)
		free(params->data->tex_south.addr);
	if (params->data->tex_west.addr)
		free(params->data->tex_west.addr);
	if (params->data->tex_east.addr)
		free(params->data->tex_east.addr);
	while (i < params->map_height)
	{
		free(params->map[i]);
		i++;
	}
	free(params->map);
}

void	free_char_array(char **line, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		free(line[i]);
		i++;
	}
	free(line);
}

//==============================================================
// print_functions
//==============================================================

void print_map_content(t_params *params)
{
    int i;

    // テクスチャパスの出力
	printf("NO : %s\n", params->data->tex_north.addr);
	printf("SO : %s\n", params->data->tex_south.addr);
	printf("WE : %s\n", params->data->tex_west.addr);
	printf("EA : %s\n", params->data->tex_east.addr);
	printf("F %d\n", params->data->floor_color);
	printf("C %d\n", params->data->ceilling_color);
	printf("map_height = %d\n", params->map_height);
	printf("map\n");
	for (i = 0; i < params->map_height; i++)
	{
		printf("%s\n", params->map[i]);
	}
}

//==============================================================
// main
//==============================================================
int main(void)
{
    char        **line;
    int         line_count;
    const char  *map_file = "test.txt";
    t_data      *data;
    t_player    *player;
    t_params    params;

    // t_data と t_player のメモリを確保
    data = malloc(sizeof(t_data));
    if (!data)
    {
        perror("malloc failed for data");
        return (1);
    }
    player = malloc(sizeof(t_player));
    if (!player)
    {
        free(data);
        perror("malloc failed for player");
        return (1);
    }

    // メモリ確保後、初期化
    memset(data, 0, sizeof(t_data));
    memset(player, 0, sizeof(t_player));
    memset(&params, 0, sizeof(t_params));

    // params 構造体にポインタを設定
    params.data = data;
    params.player = player;

    // マップデータの読み込み
    line_count = 0;
    line = read_map(map_file, &line_count);
    if (!line)
    {
        free(data);
        free(player);
        return (1);
    }

    if (parse_map(line, line_count, &params) != 0)
    {
        write(2, "Error\nInvalid map\n", 18);
        free_char_array(line, line_count);
        free(data);
        free(player);
        return (1);
    }

    // マップ内容の表示
    print_map_content(&params);

    // 使用したメモリを解放
    free_char_array(line, line_count);
    free_params(&params);
    free(data);
    free(player);

    return (0);
}
