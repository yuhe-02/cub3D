/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:31:13 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/04/28 18:27:24 by yyamasak           ###   ########.fr       */
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
