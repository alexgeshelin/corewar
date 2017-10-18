/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 11:22:40 by vtymchen          #+#    #+#             */
/*   Updated: 2016/12/06 15:34:29 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *l;

	if (alst && del)
	{
		while ((*alst))
		{
			l = (*alst)->next;
			ft_lstdelone(&(*alst), del);
			(*alst) = l;
		}
	}
}
