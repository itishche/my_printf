/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 10:50:27 by itishche          #+#    #+#             */
/*   Updated: 2019/03/13 10:50:29 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int		ft_ptr(unsigned long int c, t_buff *p, t_flags *flag)
{
	unsigned long int temp;

	flag->x = 1;
	flag->hash = 1;
	if (c == 0 && flag->tochnost == 0 && flag->dot == 1 && flag->width == 0)
		ft_write_buff(p, "0x");
	else
		check_x(p, flag, c);
	return (0);
}

void	checkbuff(t_buff *p)
{
	if (p->i >= 1900)
	{
		write(1, p->buff, p->i);
		p->count += p->i;
		p->i = 0;
	}
}
