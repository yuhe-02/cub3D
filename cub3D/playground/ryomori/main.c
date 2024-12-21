
#include "utils.h"
#include "validation.h"

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
	*line_count = 0;

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
	const char	*map_file;
	char		**line;
	int			line_count;
	int			i;
	int			j;

	map_file = "test.txt";
	line = read_map(map_file, &line_count);
	if (!line)
		return (1);

	i = 0;
	while (i < line_count)
	{
		write(1, line[i], ft_strlen(line[i]));
		i++;
	}

	write (1, "\n", 1);
	i = 0;
	while (i < line_count)
    {
		j = 0;
		while (line[i][j] != '\0')
        {
			printf("element[%d][%d] = '%c'\n", i, j, line[i][j]);
			j++;
		}
		i++;
    }

	free_char_array(line, line_count);
	return (0);
}