/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:13:22 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/03 14:11:34 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	is_valid_ascii_(char c)
{
	return (c == 'S' || c == 'W' || c == 'E' || c == 'N'
		|| c == '\t' || c == ' ' || c == '0' || c == '1');
}

static	int is_space_(int c)
{
	return (c == ' ' || c == '\t');
}

static	int is_user_dir_(char c)
{
	return (c == 'S' || c == 'W' || c == 'E' || c == 'N');
}

// static	int is_block_(char c)
// {
// 	return (c == '0' || c == '1');
// }

// static	int	check_horizontal_char_(char c, char top, char bottom)
// {
	
// }

int _check_valid_map(int len, int start_index, char **line)
{
	int	i;
	int	j;
	char	current_char;
	char	next_char;
	char	above_char;
	char	bottom_char;

	i = 0;
	// TODO if 入力予期していないアスキーの場合の処理
	// TODO if ユーザーの位置が存在しない、または複数候補があるとき
	// TODO if 壁で囲まれていない場合
	while (i < len)
	{
		j = 0;
		while (line[start_index + i][j])
		{
			if (i == 0)
				above_char = 0;
			else
				above_char = line[start_index + i - 1][j];
			if (i == len - 1)
				bottom_char = 0;
			else
				bottom_char = line[start_index + i + 1][j];
			current_char = line[start_index + i][j];
			next_char = line[start_index + i][j + 1];
			// maybe leaks detected
			// check 0 is not near space (horizontal check)
			if (j == 0 && (current_char  == '0'))
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: not locate field in left top"));
			}
			if (current_char  == '0' && (is_space_(next_char) || !next_char))
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: found space or null next to field"));
			}
			if (is_space_(current_char) && next_char == '0')
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: found space before field"));
			}
			// check 0 is not near space (vertical check)
			if (i == 0 && current_char  == '0')
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: not locate field in top"));
			}
			if (i == len - 1 && current_char  == '0')
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: not locate field in bottom"));
			}
			if (current_char == '0' && is_space_(above_char))
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: found space above"));
			}
			if (current_char == '0' && is_space_(bottom_char))
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: found space bottom"));
			}
			// check player is not near space (horizontal check)
			if (j == 0 && (is_user_dir_(current_char)))
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: player not locate field in left top"));
			}
			if (is_user_dir_(current_char)&& (is_space_(next_char) || !next_char))
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: found space or null next to player"));
			}
			if (is_space_(current_char) && is_user_dir_(current_char))
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: found space before player"));
			}
			// check player is not near space (vertical check)
			if (i == 0 && is_user_dir_(current_char))
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: player not locate in top"));
			}
			if (i == len - 1 && is_user_dir_(current_char))
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: player not locate in bottom"));
			}
			if (is_user_dir_(current_char) && is_space_(above_char))
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: found space above player"));
			}
			if (is_user_dir_(current_char) && is_space_(bottom_char))
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: found space bottom player"));
			}
			// check if valid ascii
			if (!is_valid_ascii_(current_char))
			{
				return (ft_printf_fd(ERR_FD, "Error\n%s\n" , "Invalid map: found invalid ascii"));
			}
			j++;
		}
		i++;
	}
	return (0);
}