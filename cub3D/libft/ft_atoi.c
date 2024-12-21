/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:02:33 by 1652952399        #+#    #+#             */
/*   Updated: 2024/04/28 18:26:47 by yyamasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atoi_helper(const char *start)
{
	size_t	digit_len;

	digit_len = 0;
	while (ft_isdigit(start[digit_len]))
		digit_len++;
	if (digit_len > 19)
		return (1);
	if (digit_len == 19 && ft_strncmp(start, "9223372036854775807", 19) > 0)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str == '0')
		str++;
	if (ft_atoi_helper(str))
	{
		return (-1 * (sign == 1));
	}
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
