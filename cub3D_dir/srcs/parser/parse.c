/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:53:47 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/02 16:58:22 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	free_all_line(char **line)
{
	int	line_count;

	line_count = 0;
	while (line[line_count])
		free(line[line_count++]);
	free(line);
}

static int	count_lines_(const char *map_file)
{
	char	*tmp;
	int		fd;
	int		map_size;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		error_exit("failed to open file\n", 1);
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

static	char **_read_map_(const char *map_file)
{

	char		**line;
	int			fd;
	char		*cur_line;
	int			i;
	char		*tmp;

	line = malloc((count_lines_(map_file) + 1) * sizeof(char *));
	if (!line)
		error_exit("malloc failed\n", 1);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		error_exit("failed to open file\n", 1);
	i = 0;
	while (1)
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
	char	**line;
	char	*tmp;

	tmp = ft_strrchr(map_file, '.');
	if (!tmp || ft_strncmp(tmp, ".cub", 5))
		error_exit("Invalid extensions\n", 1);
	line = _read_map_(map_file);
	if (_parse_map(line, params) != 0)
	{
		free_all_line(line);
		error_exit("Invalid map settings\n", 1);
	}
	free_all_line(line);
}
