/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 15:10:41 by vtymchen          #+#    #+#             */
/*   Updated: 2016/12/02 15:51:27 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst)
{
	unsigned char	*s;
	size_t			size;

	while (lst)
	{
		size = lst->content_size;
		s = lst->content;
		while (size--)
			ft_putchar(*s++);
		ft_putchar('\n');
		lst = lst->next;
	}
}
