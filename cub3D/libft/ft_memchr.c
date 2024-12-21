/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:30:56 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/04/28 18:27:15 by yyamasak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	find;
	unsigned char	*dest;
	size_t			i;

	find = (unsigned char)c;
	dest = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (dest[i] == find)
			return (&dest[i]);
		i++;
	}
	return (NULL);
}
