
#include "utils.h"
#include "validation.h"
#include "libft.h"

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

int	parse_color(char *line, int *color)
{
	int		i;
	int		j;
	char	**token;

	if (!line || !color)
		return (-1);
	token = ft_split(line, ',');
	fprintf(stderr, "token[0] = %s\n", token[0]);
	fprintf(stderr, "token[1] = %s\n", token[1]);
	fprintf(stderr, "token[2] = %s\n", token[2]);
	if (!token)
	{
		write(2, "Error : ft_split\n", 17);
		return (-1);
	}
	color[0] = ft_atoi(token[0]);
	color[1] = ft_atoi(token[1]);
	color[2] = ft_atoi(token[2]);

	i = 0;
	while (i < 3)
	{
		if (color[i] < 0 || color[i] > 255)
		{
			write(2, "Error : color range\n", 20);
			return (-1);
		}
		i++;
	}
	
	return (0);
}

int	parse_map(char **line, int line_count, t_element *element)
{
	int i;

	i = 0;
	while (i < line_count)
	{
		if(strncmp(line[i], "NO ", 3) == 0)
		{
			line[i] = is_spase(line[i]);
			element->texture.north_path = ft_strdup(line[i] + 3);//(\n)もコピーしてしまう可能性あり？？
			remove_newline(element->texture.north_path);
			fprintf(stderr, "element->texture.north_path = %s\n", element->texture.north_path);
		}
		else if(strncmp(line[i], "SO ", 3) == 0)
		{
			line[i] = is_spase(line[i]);
			element->texture.south_path = ft_strdup(line[i] + 3);
			remove_newline(element->texture.south_path);
			fprintf(stderr, "element->texture.south_path = %s\n", element->texture.south_path);
		}
		else if (strncmp(line[i], "WE ", 3) == 0)
		{
			line[i] = is_spase(line[i]);
			element->texture.west_path = ft_strdup(line[i] + 3);
			remove_newline(element->texture.west_path);
			fprintf(stderr, "element->texture.west_path = %s\n", element->texture.west_path);
		}
		else if (strncmp(line[i], "EA ", 3) == 0)
		{
			line[i] = is_spase(line[i]);
			element->texture.east_path = ft_strdup(line[i] + 3);
			remove_newline(element->texture.east_path);
			fprintf(stderr, "element->texture.east_path = %s\n", element->texture.east_path);
		}
		else if(strncmp(line[i], "F ", 2) == 0)
		{
			line[i] = is_spase(line[i]);
			if (parse_color(line[i] + 2, element->texture.floor_color) != 0)
			{
				write(2, "Error : floor_color\n", 21);
				return (-1);
			}
			fprintf(stderr, "floor_color[0] = %d\n", element->texture.floor_color[0]);
			fprintf(stderr, "floor_color[1] = %d\n", element->texture.floor_color[1]);
			fprintf(stderr, "floor_color[2] = %d\n", element->texture.floor_color[2]);
		}
		else if (strncmp(line[i], "C ", 2) == 0)
		{
			line[i] = is_spase(line[i]);
			if(parse_color(line[i] + 2, element->texture.ceiling_color) != 0)
			{
				write(2, "Error : ceiling_color\n", 23);
				return (-1);
			}
			fprintf(stderr, "ceiling_color[0] = %d\n", element->texture.ceiling_color[0]);
			fprintf(stderr, "ceiling_color[1] = %d\n", element->texture.ceiling_color[1]);
			fprintf(stderr, "ceiling_color[2] = %d\n", element->texture.ceiling_color[2]);
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

	element->map_height = line_count - i;//mapの開始位置を格納
	element->map_inf = malloc(element->map_height * sizeof(char *));
	if (!element->map_inf)
	{
		write(2, "malloc failed for map_inf\n", 26);
		return (-1);
	}
	int j = 0;
	while(j < element->map_height)
	{
		if (!line[i + j])
		{
			write(2, "Error : Map line is NULL\n", 25);
			return (-1);
		}
		int line_len = ft_strlen(line[i + j]);
		element->map_inf[j] = malloc((line_len + 1) * sizeof(char));
		if (!element->map_inf[j])
		{
			write(2, "Error : malloc\n", 15);
			return (-1);
		}
		int k = 0;
		while (k < line_len)
		{
			element->map_inf[j][k] = line[i + j][k];
			if (element->map_inf[j][k] == 'N' || element->map_inf[j][k] == 'S'
				|| element->map_inf[j][k] == 'E' || element->map_inf[j][k] == 'W')
			{
				element->texture.initial_value = element->map_inf[j][k];
			}
			fprintf(stderr, "map_inf[%d][%d] = %c\n", j, k, element->map_inf[j][k]); // デバッグ用出力
			k++;
		}
		element->map_inf[j][k] = '\0';
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
		(*line_count)++;
	}

	if (*line_count >= MAX_LINES)
		write (2, "Max line reached\n", 17);

	close(fd);
	return (line);
}

//==============================================================
// free_functions
//==============================================================

void	free_element(t_element *element)
{
	int	i;

	if (element->texture.north_path)
		free(element->texture.north_path);
	if (element->texture.south_path)
		free(element->texture.south_path);
	if (element->texture.east_path)
		free(element->texture.east_path);
	if (element->texture.west_path)
		free(element->texture.west_path);
	i = 0;
	while (i < element->map_height)
	{
		if (element->map_inf[i])
			free(element->map_inf[i]);
			i++;
	}
	free(element->map_inf);
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

void print_map_content(t_element *element)
{
    int i;

    // テクスチャパスの出力
    printf("NO : %s\n", element->texture.north_path);
    printf("SO : %s\n", element->texture.south_path);
    printf("WE : %s\n", element->texture.west_path);
    printf("EA : %s\n", element->texture.east_path);
	printf("initial_value : %c\n", element->texture.initial_value);

    // 色情報の出力（元のマップデータの形式で出力）
    printf("F %d,%d,%d\n", 
        element->texture.floor_color[0],
        element->texture.floor_color[1],
        element->texture.floor_color[2]);
    printf("C %d,%d,%d\n",
        element->texture.ceiling_color[0],
        element->texture.ceiling_color[1],
        element->texture.ceiling_color[2]);

    // マップ情報の出力
// マップ情報の出力 (最後の改行に注意)
for (i = 0; i < element->map_height; i++) {
    printf("%s", element->map_inf[i]);
}
printf("\n"); // 最後に改行を追加

}

//==============================================================
// main
//==============================================================
int main(void)
{
	char		**line;
	int			line_count;
	const char *map_file = "test.txt";
    t_element element;

    // 初期化
    element.texture.north_path = NULL;
    element.texture.south_path = NULL;
    element.texture.east_path = NULL;
    element.texture.west_path = NULL;
    element.map_inf = NULL;
    element.map_height = 0;

	line_count = 0;
	line = read_map(map_file, &line_count);
	if (!line)
		return (1);
	if (parse_map(line, line_count, &element) != 0)
	{
		write (2, "Error\nInvalid map\n", 18);
		free_char_array(line, line_count);
		return (1);
	}
	print_map_content(&element);

	free_char_array(line, line_count);
	return (0);
}