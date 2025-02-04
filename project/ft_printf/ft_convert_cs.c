/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_cs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:16:18 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/04 15:24:15 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convert_c(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	ft_convert_s(int fd, char *str)
{
	int	tmp;
	int	res;

	tmp = 0;
	res = 0;
	if (str == NULL)
	{
		if (write(fd, "(null)", 6) == -1)
			return (-1);
		else
			return (6);
	}
	while (tmp != -1 && *str)
	{
		tmp = write(fd, str, 1);
		if (tmp == -1)
			return (-1);
		else
			res += tmp;
		str++;
	}
	return (res);
}
