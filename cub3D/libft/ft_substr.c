/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 05:56:54 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/01 05:56:55 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			max;
	unsigned int	i;
	char			*result;

	if (!s)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
	{
		result = ft_calloc(1, 1);
		return (result);
	}
	i = start;
	max = 0;
	while (s[i++])
		max++;
	if (max < len)
		len = max;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, &s[start], len + 1);
	return (result);
}
