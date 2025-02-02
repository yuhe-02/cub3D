#include "utils.h"

void	_fill_space(int height, int width, int start_index, char **line)
{
	int		i;
	int		j;
	int		end;
	char	*tmp;

	i = 0;
	while (i < height)
	{
		tmp = (char *)malloc(sizeof(char) * (width + 1));
		if (!tmp)
			error_exit("malloc failed", 1);
		j = 0;
		while (line[start_index + i][j])
		{
			tmp[j] = line[start_index + i][j];
			j++;
		}
		while (j < width)
		{
			tmp[j++] = ' ';
		}
		tmp[j] = '\0';
		free(line[start_index + i]);
		line[start_index + i] = tmp;
		i++;
	}
}