/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 05:54:24 by yyamasak          #+#    #+#             */
/*   Updated: 2025/01/01 05:54:25 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_del(t_list **rp, void (*de)(void *), void *t, void *n_c)
{
	if (n_c != NULL)
		return (0);
	de(t);
	ft_lstclear(rp, de);
	return (1);
}

static int	ft_l(t_list **r, t_list *t, void *(*f)(void *), void (*d)(void *))
{
	void	*check;
	t_list	*new;

	while (t)
	{
		check = f(t->content);
		if (ft_check_del(r, d, check, check) == 1)
			return (1);
		new = ft_lstnew(check);
		if (ft_check_del(r, d, check, new) == 1)
			return (1);
		ft_lstadd_back(r, new);
		t = t->next;
	}
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*tmp;
	void	*check;

	if (!lst || !f || !del)
		return (NULL);
	result = NULL;
	check = f(lst->content);
	if (ft_check_del(&result, del, check, check) == 1)
		return (NULL);
	result = ft_lstnew(check);
	if (ft_check_del(&result, del, check, result) == 1)
		return (NULL);
	tmp = lst->next;
	if (ft_l(&result, tmp, f, del) == 1)
		return (NULL);
	return (result);
}
