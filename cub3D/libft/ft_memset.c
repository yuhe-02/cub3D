/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 05:54:56 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/01 05:54:57 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	src;
	unsigned char	*dest;
	size_t			i;

	src = (unsigned char)c;
	dest = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		*dest = src;
		dest++;
		i++;
	}
	return (b);
}
