/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:18:07 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/04 15:24:11 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_convert_d_h(int fd, int num, int res)
{
	int	tmp;

	if (res == -1)
		return (-1);
	if (num >= 10)
	{
		tmp = ft_convert_d_h(fd, num / 10, res);
		if (tmp == -1)
			return (-1);
		else
			res += tmp;
	}
	tmp = ft_convert_c(fd, '0' + num % 10);
	if (tmp == -1)
		return (-1);
	else
		return (res + tmp);
}

int	ft_convert_d(int fd, int num)
{
	int	res;

	res = 0;
	if (num == -2147483648)
	{
		if (write(fd, "-2147483648", 11) == -1)
			return (-1);
		else
			return (11);
	}
	if (num < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (-1);
		else
			res += 1;
		num *= -1;
	}
	res += ft_convert_d_h(fd, num, 0);
	return (res);
}
