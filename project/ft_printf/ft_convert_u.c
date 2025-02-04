/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:16:48 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/04 15:24:03 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_convert_u_h(int fd, unsigned int num, int res)
{
	int	tmp;

	if (res == -1)
		return (-1);
	if (num >= 10)
	{
		tmp = ft_convert_u_h(fd, num / 10, res);
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

int	ft_convert_u(int fd, unsigned int num)
{
	return (ft_convert_u_h(fd, num, 0));
}
