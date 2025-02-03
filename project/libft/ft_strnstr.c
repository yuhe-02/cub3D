/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 05:56:35 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/01 05:56:36 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	if (!haystack && len == 0)
		return (NULL);
	if (*haystack)
		i = 0;
	i = 0;
	needle_len = ft_strlen((char *)needle);
	if (needle_len == 0 && ft_memcmp(&haystack[i], needle, needle_len) == 0)
		return ((char *)&haystack[i]);
	while (i + needle_len <= len && haystack[i])
	{
		if (ft_memcmp(&haystack[i], needle, needle_len) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
