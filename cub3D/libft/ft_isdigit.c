/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:30:53 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/04/20 00:06:25 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c < -1 || c > 255)
		return (0);
	if ('0' <= (unsigned char)c && (unsigned char)c <= '9')
		return (1);
	else
		return (0);
}
