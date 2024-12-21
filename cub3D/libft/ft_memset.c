/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:31:17 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/04/28 18:27:27 by yyamasak           ###   ########.fr       */
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
