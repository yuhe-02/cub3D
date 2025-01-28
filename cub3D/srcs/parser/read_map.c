/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:42:30 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/28 13:39:27 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	count_lines(const char *map_file)
{
	char	*tmp;
	int		fd;
	int		map_size;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		perror("Faild to open file");
		exit(1);
	}
	map_size = 0;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		free(tmp);
		map_size++;
	}
	close(fd);
	return (map_size);
}

char **read_map(const char *map_file, int *line_count)
{

	char		**line;
	int			fd;
	char		*cur_line;
	int			i;
	char		*tmp;

	*line_count = count_lines(map_file);
	line = malloc((*line_count + 1) * sizeof(char *));
	if (!line)
	{
		perror("malloc");
		exit(1);
	}
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
	{
		perror("Faild to open file");
		exit(1);
	}
	i = 0;
	while (i < *line_count)
	{
		cur_line = get_next_line(fd);
		if (!cur_line)
			break ;
		tmp = ft_strtrim(cur_line, "\n");
		free(cur_line);
		line[i] = tmp;
		i++;
	}
	close(fd);
	line[i] = NULL;
	return (line);
}
