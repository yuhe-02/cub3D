/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:13:22 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/02 16:01:43 by yyamasak         ###   ########.fr       */
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

static	int is_block_(char c)
{
	return (c == '0' || c == '1');
}

int _check_valid_map(int len, int start_index, char **line)
{
	int	i;
	int	j;
	int		space_flg;
	int		user_dir_flg;
	int		start_flg;
	char	current_char;
	char	next_char;
	char	above_char;
	char	bottom_char;

	i = 0;
	space_flg = 0;
	user_dir_flg = 0;
	start_flg = 0;
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
				error_exit("Invalid map: not locate field in left top\n", 1);
			}
			if (current_char  == '0' && (is_space_(next_char) || !next_char))
			{
				error_exit("Invalid map: found space or null next to field\n", 1);
			}
			if (is_space_(current_char) && next_char == '0')
			{
				error_exit("Invalid map: found space before field\n", 1);
			}
			// check 0 is not near space (vertical check)
			if (i == 0 && current_char  == '0')
			{
				error_exit("Invalid map: not locate field in top\n", 1);
			}
			if (i == len - 1 && current_char  == '0')
			{
				error_exit("Invalid map: not locate field in bottom\n", 1);
			}
			if (current_char == '0' && is_space_(above_char))
			{
				error_exit("Invalid map: found space above\n", 1);
			}
			if (current_char == '0' && is_space_(bottom_char))
			{
				error_exit("Invalid map: found space bottom\n", 1);
			}

			if (j == 0 && (is_user_dir_(current_char)))
			{
				error_exit("Invalid map: player not locate field in left top\n", 1);
			}
			if (is_user_dir_(current_char)&& (is_space_(next_char) || !next_char))
			{
				error_exit("Invalid map: found space or null next to player\n", 1);
			}
			if (is_space_(current_char) && is_user_dir_(current_char))
			{
				error_exit("Invalid map: found space before player\n", 1);
			}
			// check 0 is not near space (vertical check)
			if (i == 0 && is_user_dir_(current_char))
			{
				error_exit("Invalid map: player not locate in top\n", 1);
			}
			if (i == len - 1 && is_user_dir_(current_char))
			{
				error_exit("Invalid map: player not locate in bottom\n", 1);
			}
			if (is_user_dir_(current_char) && is_space_(above_char))
			{
				error_exit("Invalid map: found space above player \n", 1);
			}
			if (is_user_dir_(current_char) && is_space_(bottom_char))
			{
				error_exit("Invalid map: found space bottom player \n", 1);
			}


			// check if valid ascii
			if (!is_valid_ascii_(current_char))
				error_exit("Invalid map: found invalid ascii\n", 1);
			j++;
		}
		i++;
	}
	return (0);
}