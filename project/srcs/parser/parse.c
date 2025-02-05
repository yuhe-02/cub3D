/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:53:47 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/05 22:45:02 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

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
		return (-1);
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

static char	*gnl_without_nl(int fd)
{
	char	*line;
	char	*tmp;

	line = get_next_line(fd);
	if (!line)
		return (0);
	tmp = ft_strtrim(line, "\n");
	free(line);
	return (tmp);
}

static int	_read_map_(const char *map_file, char ***line, int line_len)
{
	int		fd;
	char	*cur_line;
	int		i;

	(*line) = malloc((line_len + 1) * sizeof(char *));
	if (!(*line))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR3, ERR_ALLOC));
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR3, ERR_OPEN));
	i = 0;
	while (1)
	{
		cur_line = gnl_without_nl(fd);
		if (!cur_line)
			break ;
		(*line)[i] = cur_line;
		i++;
	}
	close(fd);
	(*line)[i] = NULL;
	return (0);
}

int	_parse(const char *map_file, t_params *params)
{
	char	**line;
	char	*tmp;
	int		err;
	int		line_len;

	tmp = ft_strrchr(map_file, '.');
	if (!tmp || ft_strncmp(tmp, ".cub", 5))
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR2, ERR_NOEXT));
	line_len = count_lines_(map_file);
	if (line_len == -1)
		return (ft_printf_fd(ERR_FD, "Error\n%s%s\n", ERR3, ERR_OPEN));
	if (_read_map_(map_file, &line, line_len))
		return (1);
	err = _parse_map(line, params);
	free_all_line(line);
	if (err)
		return (1);
	return (0);
}
