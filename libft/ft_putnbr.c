/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 12:09:32 by vtymchen          #+#    #+#             */
/*   Updated: 2016/11/30 12:12:58 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	unsigned int unb;

	unb = nb;
	if (nb < 0)
	{
		unb = nb * -1;
		ft_putchar('-');
	}
	if (unb > 9)
		ft_putnbr(unb / 10);
	ft_putchar(unb % 10 + '0');
}
