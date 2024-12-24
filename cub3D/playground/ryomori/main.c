
#include "utils.h"
#include "validation.h"

char *is_spase(char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
	{
		i++;
	}
	return (str[i]);
}



int	parse_color(char *line, int *color)
{
	int		i;
	int		j;
	char	**token;

	if (!line || !color)
		return (-1);
	token = ft_split(line, ',');
	if (!token)
		return (-1);
	i = 0;
	while(token[i])
		i++;
	if (i != 3)
	{
		i = 0;
		while(token[i])
			free(token[i++]);
		free(token);
		return (-1);
	}
	i = 0;
	while (i < 3)
		{
			j = 0;
			while (token[i][j])
			{
				if (!isdigit(token[i][j]))
				{
					while (token[j])
						free(token[j++]);
					free(token);
					return (-1);
				}
				j++;
			}
			color[i] = ft_atoi(token[i]);
			if (color[i] < 0 || color[i] > 255)
			{
				while (token[j])
					free(token[j++]);
				free(token);
				return (-1);
			}
			i++;
		}
		i = 0;
		while (token[i])
			free(token[i++]);
		free(token);
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

int	parse_map(char **line, int line_count, t_element *element)
{
	int i;

	i = 0;
	while (i < line_count)
	{
		if(strncmp(line[i], "NO ", 3) == 0)
		{
			is_spase(line[i]);
			element->texture.north_path = ft_strdup(line[i] + 3);//(\n)もコピーしてしまう可能性あり？？
		}
		else if(strncmp(line[i], "SO ", 3) == 0)
		{
			is_spase(line[i]);
			element->texture.south_path = ft_strdup(line[i] + 3);
		}
		else if (strncmp(line[i], "WE ", 3) == 0)
		{
			is_spase(line[i]);
			element->texture.west_path = ft_strdup(line[i] + 3);
		}
		else if (strncmp(line[i], "EA ", 3) == 0)
		{
			is_spase(line[i]);
			element->texture.east_path = ft_strdup(line[i] + 3);
		}
		else if(strncmp(line[i], "F ", 2) == 0)
		{
			is_spase(line[i]);
			if (parse_color(line[i] + 2, element->texture.floor_color) != 0)
			fprintf(stderr, "Error : floor_color\n");
			return (-1);
		}
		else if (strncmp(line[i], "C ", 2) == 0)
		{
			if(parse_color(line[i] + 2, element->texture.ceiling_color) != 0)
			fprintf(stderr, "Error : ceiling_color");
			return (-1);
		}
		else if(line[i][0] == '\0')//空欄の行のとき
		{
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
		element->map_inf[j] = ft_strdup(line[i + j]);
		if (!element->map_inf[j])
		{
			write(2, "Error : ft_strdup\n", 18);
			return (-1);
		}
		j++;
	}
	return (0);
}

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

	free_char_array(line, line_count);
	return (0);
}