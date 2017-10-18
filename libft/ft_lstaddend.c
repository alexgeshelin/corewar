/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 15:08:30 by vtymchen          #+#    #+#             */
/*   Updated: 2016/12/06 16:46:12 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **lst, t_list *elem)
{
	t_list *l;

	if (!elem && !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = elem;
		return ;
	}
	l = *lst;
	while (l->next)
		l = l->next;
	l->next = elem;
}
