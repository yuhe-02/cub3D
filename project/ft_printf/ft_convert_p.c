/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:16:33 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/04 15:24:08 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_convert_p_h(int fd, unsigned long long num, int res)
{
	int	tmp;

	if (res == -1)
		return (-1);
	if (num >= 16)
	{
		tmp = ft_convert_p_h(fd, num / 16, res);
		if (tmp == -1)
			return (-1);
		else
			res += tmp;
	}
	tmp = ft_convert_c(fd, "0123456789abcdef"[num % 16]);
	if (tmp == -1)
		return (-1);
	else
		return (res + tmp);
}

int	ft_convert_p(int fd, void *address)
{
	unsigned long long	num;
	int					res;

	num = (unsigned long long)address;
	res = 0;
	if (write(fd, "0x", 2) == -1)
		return (-1);
	else
		res += 2;
	res += ft_convert_p_h(fd, num, 0);
	return (res);
}
