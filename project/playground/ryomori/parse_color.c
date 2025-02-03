#include "raycast.h"
#include "libft.h"
#include "raycast.h"


//==============================================================
// parse_color : RGBの値の範囲をチェック
//==============================================================

int	is_valid_rgb(int value)
{
	return (value >= 0 && value <= 255);
}
//==============================================================
// parse_color : RGBを16進数に変換
//==============================================================

int	convert_rgb_hex(int *rgb_colors)
{
	int	hex_color;
	int	i;

	i = 0;
	while(i < 3)
	{
		hex_color = hex_color * 256 + rgb_colors[i];
		i++;
	}
	return (hex_color);
}

//==============================================================
// parse_color : RGB文字列を分割しint型に変換
//==============================================================

int	parse_rgb_values(char **rgb, int *rgb_colors)
{
	int	i;

	i = 0;
	while(i < 3)
	{
		rgb_colors[i] = ft_atoi(rgb[i]);
		if (!is_valid_rgb(rgb_colors[i]))
		{
			write(2, "Error : color range\n", 20);
			return (-1);
		}
		i++;
	}
	return (0);
}
//==============================================================
// parse_color : char **開放
//==============================================================

void free_char_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i] != NULL)
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
}
//==============================================================
// parse_color : main
//==============================================================
int		parse_color(char *line, int *color)
{
	char	**rgb;
	int		rgb_color[3];

	if (!line)
		return (-1);
	rgb = ft_split(line, ',');
	if (!rgb)
	{
		write(2, "Error : split\n", 14);
		return (-1);
	}
	
	if (parse_rgb_values(rgb, rgb_color) != 0)
	{
		free_char_rgb(rgb);
		return (-1);
	}

	*color = convert_rgb_hex(rgb_color);

	free_char_rgb(rgb);
	return (0);
}