/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 05:54:52 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/01 05:54:53 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tmp_d;
	const char	*tmp_s;

	if (!dst && !src)
		return (dst);
	tmp_d = (char *)dst;
	tmp_s = (const char *)src;
	if (dst <= src)
	{
		while (len-- > 0)
		{
			*tmp_d++ = *tmp_s++;
		}
	}
	else
	{
		tmp_d += len - 1;
		tmp_s += len - 1;
		while (len-- > 0)
		{
			*tmp_d-- = *tmp_s--;
		}
	}
	return (dst);
}
