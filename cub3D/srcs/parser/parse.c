/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:53:47 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/28 15:06:30 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	count_lines_(const char *map_file)
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

static	char **_read_map_(const char *map_file, int *line_count)
{

	char		**line;
	int			fd;
	char		*cur_line;
	int			i;
	char		*tmp;

	*line_count = count_lines_(map_file);
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

void	_parse(const char *map_file, t_params *params)
{
	int		line_count;
	char	**line;

	line_count = 0;
	line = _read_map_(map_file, &line_count);
	if (_parse_map(line, line_count, params) != 0)
	{
		write(2, "Error\nInvalid map\n", 18);
		exit(1);
	}
}