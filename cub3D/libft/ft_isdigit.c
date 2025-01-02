/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 05:53:18 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/01 05:53:19 by yyamasak         ###   ########.fr       */
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
