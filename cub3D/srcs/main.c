#include "utils.h"

char world_map[mapHeight][mapWidth + 1] = 
{
  "111111111111111111111111",
  "102000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000222220000202020001",
  "100000200020000000000001",
  "100000200020000200020001",
  "100000200020000000000001",
  "100000220220000202020001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "100000000000000000000001",
  "122222222000000000000001",
  "120200002000000000000001",
  "120000202000000000000001",
  "120200002000000000000001",
  "120222222000000000000001",
  "120000000000000000000001",
  "122222222000000000000001",
  "111111111111111111111111"
};

// char world_map[mapWidth][mapHeight + 1] = 
// {
//   "111",
//   "101",
//   "111",
// };

int	main_loop(void *arg)
{
	t_params	*params;
	t_data		*data;
	t_player	*player;

	params = (t_params *)arg;
	data = params->data;
	player = params->player;
	if (data->mlx && data->win && data->img.img)
		ft_bzero(data->img.addr, data->img.llen * data->img.height);
	_update_player(params, player);
	_raycast(params);
	if (data->mlx && data->win && data->img.img)
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

int parse_map(char **line, int line_count, t_params *params)
{
	int start_index;
	
	start_index = parse_map_settings(line, line_count, params);
	if (start_index < 0)
		return (-1);
	parse_map_data(line, start_index, line_count, params);
	return (0);
}

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

	while (1)
	{
		cur_line = get_next_line(fd);
		if (!cur_line)
			break ;
		if (*line_count > MAX_LINES)
			break ;
		line[*line_count] = cur_line;
		(*line_count)++;
	}

	if (*line_count >= MAX_LINES)
		write (2, "Max line reached\n", 17);

	close(fd);
	return (line);
}

int	main(void)
{
	t_params	params;
	t_data		data;
	t_player	player;
	t_ray		ray;
	int			line_count;
	const char	*map_file = "test.txt";
	char		**line;

	_init_params(&params, &data, &ray, &player, world_map);
	line_count = 0;
	line = read_map(map_file, &line_count);
	if (parse_map(line, line_count, &params) != 0)
	{
		write(2, "Error\nInvalid map\n", 18);
		// free_all_structs(line, line_count, &params);
		return (1);
	}
	// printf("%s\n", line[0]);
	// for (int k = 0; k < params.map_height; k++) {
	// 	printf("%s\n", params.map[k]);
	// }
	_init_data(&data);
	_init_player(&player, 2, 2);
	printf("user pos: %f, %f\n", player.pos.x, player.pos.y);
	set_event(&data, &params);
	mlx_loop_hook(data.mlx, &main_loop, (void *)&params);
	mlx_loop(data.mlx);
	return (0);
}