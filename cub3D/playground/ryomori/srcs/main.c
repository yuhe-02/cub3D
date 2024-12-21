#include "utils.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int close_window(t_data *data) {
    mlx_destroy_image(data->mlx, data->img);
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
}

int key_hook(int keycode, t_data *data) {
    if (keycode == 65307) // ESC key
        close_window(data);
    return (0);
}

void draw_julia_set(t_data *img) {

	// C の実部と虚部
	double	cx = -0.3;
	double	cy = -0.63;

    // フラクタルの描画処理
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            double zx = (x - (WIDTH / 2)) / (0.5 * img->zoom * WIDTH) + img->offsetX;
            double zy = (y - (HEIGHT / 2)) / (0.5 * img->zoom *HEIGHT) + img->offsetY;
            int i = 0;
            while (zx * zx + zy * zy < 4 && i < ACRAC) {
                double tmp = zx * zx - zy * zy + cx;
                zy = 2.0 * zx * zy + cy;
                zx = tmp;
                i++;
            }
            if (i == ACRAC)
                i = 0;
            int color = i * 10000;
            my_mlx_pixel_put(img, x, y, color);
        }
    }
    mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}


int mouse_hook(int button, int x, int y, void *param) {
    t_data *img = (t_data *)param;
    if (button == 4) { // マウスホイールアップ（ズームイン）
        img->zoom *= 1.2;
    } else if (button == 5) { // マウスホイールダウン（ズームアウト）
        img->zoom /= 1.2;
    }
    mlx_clear_window(img->mlx, img->win);
    draw_julia_set(img);
    return 0;
}

int	main(void)
{    // MiniLibX の初期化
    void	*mlx = mlx_init();
    void	*win = mlx_new_window(mlx, WIDTH, HEIGHT, "Julia Set");
    t_data	img;

    img.mlx = mlx;
    img.win = win;
    img.img = mlx_new_image(img.mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    img.zoom = 1.0;
    img.offsetX = 0.0;
    img.offsetY = 0.0;

	draw_julia_set(&img);

    mlx_hook(img.win, 17, 0, close_window, &img);
    mlx_key_hook(img.win, key_hook, &img);
    mlx_mouse_hook(img.win, mouse_hook, &img);
    mlx_loop(img.mlx);

    return (0);
}