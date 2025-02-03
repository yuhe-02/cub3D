
#include "utils.h"
#include "libft.h"
#include "raycast.h"

void	free_char_array(char **line, int line_count);

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

//==============================================================
// parse_functions
//==============================================================

int		parse_color(char *line, int *color)
{
	int		i;
	char	**rgb;
	int		hex_color;
	int		rgb_color[3];

	if (!line)
		return (-1);
	rgb = ft_split(line, ',');
	if (!rgb)
	{
		write(2, "Error : split\n", 14);
		return (-1);
	}
	
	rgb_color[0] = ft_atoi(rgb[0]);
	rgb_color[1] = ft_atoi(rgb[1]);
	rgb_color[2] = ft_atoi(rgb[2]);

	i = 0;
	while(i < 3)
	{
		if (rgb_color[i] < 0 || rgb_color[i] > 255)
		{
			write(2, "Error : color range\n", 20);
			free_char_array(rgb, 3);
			return (-1);
		}
		i++;
	}
	i = 0;
	hex_color = 0;
	while (i < 3)
	{
		hex_color = hex_color * 256;
		hex_color += rgb_color[i];
		i++;
	}
	*color = hex_color;

	i = 0;
	while (rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
	return (0);
}


//==============================================================
// parse_map
//==============================================================

int	parse_map(char **line, int line_count, t_params *params)
{
	int i;

	i = 0;
	while (i < line_count)
	{
		if(strncmp(line[i], "NO ", 3) == 0)
		{
			line[i] = is_spase(line[i]);
			params->data->tex_north.addr = ft_strdup(line[i] + 3);
			remove_newline(params->data->tex_north.addr);
			fprintf(stderr, "tex_north.img = %s\n", params->data->tex_north.addr);
		}
		else if(strncmp(line[i], "SO ", 3) == 0)
		{
			line[i] = is_spase(line[i]);
			params->data->tex_south.addr = ft_strdup(line[i] + 3);
			remove_newline(params->data->tex_south.addr);
			fprintf(stderr, "tex_south.img = %s\n", params->data->tex_south.addr);
		}
		else if (strncmp(line[i], "WE ", 3) == 0)
		{
			line[i] = is_spase(line[i]);
			params->data->tex_west.addr = ft_strdup(line[i] + 3);
			remove_newline(params->data->tex_west.addr);
			fprintf(stderr, "params->data->tex_west = %s\n", params->data->tex_west.addr);
		}
		else if (strncmp(line[i], "EA ", 3) == 0)
		{
			line[i] = is_spase(line[i]);
			params->data->tex_east.addr = ft_strdup(line[i] + 3);
			remove_newline(params->data->tex_east.addr);
			fprintf(stderr, "params->data->tex_east.img = %s\n",params->data->tex_east.addr);
		}
		else if(strncmp(line[i], "F ", 2) == 0)
		{
			line[i] = is_spase(line[i]);
			if (parse_color(line[i] + 2, &params->data->floor_color ) != 0)
			{
				write(2, "Error : floor_color\n", 21);
				return (-1);
			}
			fprintf(stderr, "floor_color = %d\n", params->data->floor_color);
		}
		else if (strncmp(line[i], "C ", 2) == 0)
		{
			line[i] = is_spase(line[i]);
			if(parse_color(line[i] + 2, &params->data->ceilling_color) != 0)
			{
				write(2, "Error : ceiling_color\n", 23);
				return (-1);
			}
			fprintf(stderr, "ceilling_color = %d\n", params->data->ceilling_color);
		}
		else if(line[i][0] == '\n' && line[i][1] == '\0')//空欄の行のとき
		{
			fprintf(stderr, "spase line\n");
			i++;
			continue;
		}
		else
		{
			break;
		}
		i++;
	}

	params->map_height = line_count - i;//mapの開始位置を格納 すべての行数―現在の行数
	params->map = malloc(params->map_height * sizeof(char *));
	if (!params->map)
	{
		write(2, "malloc failed for map\n", 23);
		return (-1);
	}
	int j = 0;
	while(j < params->map_height)
	{
		if (!line[i + j])
		{
			write(2, "Error : Map line is NULL\n", 25);
			return (-1);
		}
		int line_len = ft_strlen(line[i + j]);
		params->map[j] = malloc(line_len + 1);
		if (!params->map[j])
		{
			write(2, "Error : malloc\n", 15);
			return (-1);
		}
		int k = 0;
		while (k < line_len)
		{
			// element->map_inf[j][k] = line[i + j][k];
			params->map[j][k] = line[i + j][k];
			if (params->map[j][k] == 'N')
			{
				params->player->init_userdir_x = 0;
				params->player->init_userdir_y = -1;
				params->player->init_userpos_x = k;
				params->player->init_userpos_y = j;
			}
			else if (params->map[j][k] == 'S')
			{
				params->player->init_userdir_x = 0;
				params->player->init_userdir_y = 1;
				params->player->init_userpos_x = k;
				params->player->init_userpos_y = j;
			}
			else if (params->map[j][k] == 'W')
			{
				params->player->init_userdir_x = -1;
				params->player->init_userdir_y = 0;
				params->player->init_userpos_x = k;
				params->player->init_userpos_y = j;
			}
			else if (params->map[j][k] == 'E')
			{
				params->player->init_userdir_x = 1;
				params->player->init_userdir_y = 0;
				params->player->init_userpos_x = k;
				params->player->init_userpos_y = j;
			}
			fprintf(stderr, "params->player->init_userdir_x = %d\n", params->player->init_userdir_x);
			fprintf(stderr, "params->player->init_userdir_y = %d\n", params->player->init_userdir_y);
			fprintf(stderr, "params->player->init_userpos_x = %d\n", params->player->init_userpos_x);
			fprintf(stderr, "params->player->init_userpos_y = %d\n", params->player->init_userpos_y);
			k++;
		}
		params->map[j][k] = '\0';
		j++;
	}
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
	char		**line;
	int			line_count;
	const char *map_file = "test.txt";
    t_data data;
	t_player player;
	t_params params;


    // 初期化
	memset(&data, 0, sizeof(t_data));
	memset(&player, 0, sizeof(t_player));
	memset(&params, 0, sizeof(t_params));

	// マップデータの読み込み

	line_count = 0;
	line = read_map(map_file, &line_count);
	if (!line)
		return (1);
	if (parse_map(line, line_count, &params) != 0)
	{
		write (2, "Error\nInvalid map\n", 18);
		free_char_array(line, line_count);
		return (1);
	}
	print_map_content(&params);

	free_char_array(line, line_count);
	return (0);
}