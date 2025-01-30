#include "utils.h"

int	main_loop(void *arg)
{
	t_params	*params;
	t_data		*data;
	t_player	*player;

	params = (t_params *)arg;
	data = &(params->data);
	player = &(params->player);
	if (data->mlx && data->win && data->img.img)
		ft_bzero(data->img.addr, data->img.llen * data->img.height);
	_update_player(params, player);
	_raycast(params);
	if (data->mlx && data->win && data->img.img)
		mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
static  void check_all_set_(t_params *params)
{
  if (!params->data.tex_north.path)
    error_exit("north path not set\n", 1);
  if (!params->data.tex_south.path)
    error_exit("south path not set\n", 1);
  if (!params->data.tex_west.path)
    error_exit("west path not set\n", 1);
  if (!params->data.tex_east.path)
    error_exit("east path not set\n", 1);
  if (params->data.ceilling_color == -1)
    error_exit("ceiling color not set\n", 1);
  if (params->data.floor_color == -1)
    error_exit("floor color not set\n", 1);
  if (params->player.init_userpos_x == -1)
    error_exit("player position not set\n", 1);
}
int	main(int argc, char **argv)
{
	t_params	*params;

  if (argc == 1)
    error_exit("need arguments\n", 1);
  if (argc != 2)
    error_exit("too many arguments\n", 1);
	params = _init_params();
	_parse(argv[1], params);
  check_all_set_(params);
	_init_data(&(params->data));
	_init_player(&(params->player));
	set_event(&(params->data), params);
	mlx_loop_hook(params->data.mlx, &main_loop, (void *)params);
	mlx_loop(params->data.mlx);
	return (0);
}