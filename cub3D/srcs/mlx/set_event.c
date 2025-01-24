#include "utils.h"

void	set_event(t_data *data, t_params *params) 
{
	mlx_hook(data->win, 17, 0, close_window, params);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_hook, params);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release_hook, params);
}