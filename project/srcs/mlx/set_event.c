#include "raycast.h"

void	set_event(t_data *data, t_params *params) 
{
	mlx_hook(data->win, 17, 0, _close_window, params);
	mlx_hook(data->win, KeyPress, KeyPressMask, _key_hook, params);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, _key_release_hook, params);
}