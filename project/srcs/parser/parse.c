/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:53:47 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/03 13:19:50 by yyamasak         ###   ########.fr       */
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

// static	char **_read_map_(const char *map_file)
// {

// 	char		**line;
// 	int			fd;
// 	char		*cur_line;
// 	int			i;
// 	char		*tmp;

// 	line = malloc((count_lines_(map_file) + 1) * sizeof(char *));
// 	if (!line)
// 		error_exit("malloc failed\n", 1);
// 	fd = open(map_file, O_RDONLY);
// 	if (fd == -1)
// 		error_exit("failed to open file\n", 1);
// 	i = 0;
// 	while (1)
// 	{
// 		cur_line = get_next_line(fd);
// 		if (!cur_line)
// 			break ;
// 		tmp = ft_strtrim(cur_line, "\n");
// 		free(cur_line);
// 		line[i] = tmp;
// 		i++;
// 	}
// 	close(fd);
// 	line[i] = NULL;
// 	return (line);
// }

static	int	_read_map_(const char *map_file, char ***line)
{
	int			fd;
	char		*cur_line;
	int			i;
	char		*tmp;
	int			line_len;

	line_len = count_lines_(map_file);
	if (line_len == -1)
		return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "failed to open file"));
	(*line) = malloc((line_len + 1) * sizeof(char *));
	if (!(*line))
		return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "malloc failed"));
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "failed to open file"));
	i = 0;
	while (1)
	{
		cur_line = get_next_line(fd);
		if (!cur_line)
			break ;
		tmp = ft_strtrim(cur_line, "\n");
		free(cur_line);
		(*line)[i] = tmp;
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

	tmp = ft_strrchr(map_file, '.');
	if (!tmp || ft_strncmp(tmp, ".cub", 5))
		return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid extensions"));
	if (_read_map_(map_file, &line))
		return (1);
	err = _parse_map(line, params);
	free_all_line(line);
	if (err)
		return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map settings"));
	return (0);
}
