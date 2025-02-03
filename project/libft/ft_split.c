/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 05:55:30 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/01 05:55:38 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	size_t	start;
	size_t	end;

	if (!s)
		return (0);
	start = 0;
	count = 0;
	while (s[start])
	{
		while (s[start] && s[start] == c)
			start = start + 1;
		end = start;
		while (s[end] && s[end] != c)
			end = end + 1;
		if (end > start)
			count++;
		start = end;
	}
	return (count);
}

static	void	ft_check_free(char ***result_p, size_t count)
{
	if ((*result_p)[count] != NULL)
		return ;
	while (count > 0)
	{
		count--;
		free((*result_p)[count]);
	}
	free(*result_p);
	*result_p = NULL;
}

static void	ft_help(char ***result_p, char const *s, char c)
{
	size_t	start;
	size_t	end;
	size_t	count;

	start = 0;
	count = 0;
	while (s[start])
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		if (end <= start)
			continue ;
		(*result_p)[count] = ft_substr(s, (unsigned int)start, end - start);
		ft_check_free(result_p, count);
		if (!(*result_p))
			return ;
		start = end;
		count++;
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**result;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	result[words] = NULL;
	ft_help(&result, s, c);
	if (!result)
		return (NULL);
	return (result);
}
