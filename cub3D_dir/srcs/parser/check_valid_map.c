/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:13:22 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/30 14:21:19 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	_is_valid_ascii_(char c)
{
	return (c == 'S' || c == 'W' || c == 'E' || c == 'N'
		|| c == '\t' || c == ' ' || c == '0' || c == '1');
}

int _check_valid_map(int len, int start_index, char **line)
{
	int	i;
	int	j;

	i = 0;
	// TODO if 入力予期していないアスキーの場合の処理
	// TODO if ユーザーの位置が存在しない、または複数候補があるとき
	// TODO if 壁で囲まれていない場合
	while (i < len)
	{
		j = 0;
		while (line[start_index + i][j])
		{
			if (!_is_valid_ascii_(line[start_index + i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}