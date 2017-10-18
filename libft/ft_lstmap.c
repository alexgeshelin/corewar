/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 15:09:32 by vtymchen          #+#    #+#             */
/*   Updated: 2016/12/06 17:11:39 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *head;

	if (!lst || !f)
		return (NULL);
	head = (f)(lst);
	new = head;
	lst = lst->next;
	while (lst)
	{
		new->next = (f)(lst);
		new = new->next;
		lst = lst->next;
	}
	return (head);
}
