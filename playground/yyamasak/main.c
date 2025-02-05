#include "raycast.h"

char	world_map[mapHeight][mapWidth + 1] = {"111111111111111111111111",
		"102000000000000000000001", "100000000000000000000001",
		"100000000000000000000001", "100000222220000202020001",
		"100000200020000000000001", "100000200020000200020001",
		"100000200020000000000001", "100000220220000202020001",
		"100000000000000000000001", "100000000000000000000001",
		"100000000000000000000001", "100000000000000000000001",
		"100000000000000000000001", "100000000000000000000001",
		"100000000000000000000001", "122222222000000000000001",
		"120200002000000000000001", "120000202000000000000001",
		"120200002000000000000001", "120222222000000000000001",
		"120000000000000000000001", "122222222000000000000001",
		"111111111111111111111111"};

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

int	main(void)
{
	t_params params;
	t_data data;
	t_player player;
	t_ray ray;

	_init_data(&data);
	_init_player(&player, 2, 2);
	_init_params(&params, &data, &ray, &player, world_map);
	set_event(&data, &params);
	mlx_loop_hook(data.mlx, &main_loop, (void *)&params);
	mlx_loop(data.mlx);
	return (0);
}