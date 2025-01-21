/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 05:52:36 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/01 06:30:41 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*result;

	if (size != 0 && SIZE_MAX / size < count)
	{
		return (NULL);
	}
	result = malloc(count * size);
	if (!result)
	{
		return (NULL);
	}
	ft_bzero(result, count * size);
	return (result);
}
