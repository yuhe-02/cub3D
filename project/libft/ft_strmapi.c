/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 05:56:26 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/01 05:56:26 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	result = ft_strdup(s);
	if (!result)
		return (NULL);
	len = (unsigned int)ft_strlen(s);
	while (i < len)
	{
		result[i] = f(i, result[i]);
		i++;
	}
	return (result);
}
