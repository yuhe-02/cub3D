/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:17:14 by yyamasak          #+#    #+#             */
/*   Updated: 2025/02/03 11:17:15 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_formats(int fd, char fmt, va_list *arg)
{
	if (fmt == '%')
		return (ft_convert_c(fd, '%'));
	else if (fmt == 'c')
		return (ft_convert_c(fd, (char)va_arg(*arg, int)));
	else if (fmt == 's')
		return (ft_convert_s(fd, va_arg(*arg, char *)));
	else if (fmt == 'p')
		return (ft_convert_p(fd, va_arg(*arg, void *)));
	else if (fmt == 'd')
		return (ft_convert_d(fd, va_arg(*arg, int)));
	else if (fmt == 'i')
		return (ft_convert_d(fd, va_arg(*arg, int)));
	else if (fmt == 'u')
		return (ft_convert_u(fd, va_arg(*arg, unsigned int)));
	else if (fmt == 'x')
		return (ft_convert_x(fd, va_arg(*arg, unsigned int)));
	else if (fmt == 'X')
		return (ft_convert_x2(fd, va_arg(*arg, unsigned int)));
	return (-1);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	int		i;
	int		ans;
	int		result;
	va_list	arg;

	i = 0;
	ans = 0;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			result = ft_formats(fd, format[i], &arg);
		}
		else
			result = ft_convert_c(fd, format[i]);
		if (result == -1)
			return (-1);
		else
			ans += result;
		i++;
	}
	va_end(arg);
	return (ans);
}

// int	ft_printf(const char *format, ...)
// {
// 	va_list	args;
// 	int		result;

// 	va_start(args, format);
// 	result = ft_printf_fd(STDOUT_FILENO, format, args);
// 	va_end(args);
// 	return (result);
// }