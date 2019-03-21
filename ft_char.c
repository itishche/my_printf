/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:39:20 by itishche          #+#    #+#             */
/*   Updated: 2019/02/11 12:39:24 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int			ft_char(void *c, t_buff *p, t_flags *flag)
{
	unsigned char	c2;

	if (flag->width != 0)
		flag->width--;
	if (flag->minus == 0 && flag->zero == 0)
		space(p, flag->width);
	if (flag->minus == 0 && flag->zero == 1)
		fzero(p, flag->width);
	c2 = (unsigned char)c;
	p->buff[p->i++] = c2;
	if (flag->minus == 1)
		space(p, flag->width);
	return (0);
}

static	int	znak(int sign)
{
	return (sign == 1 ? -1 : 0);
}

int			ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\n' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	if (number > 9223372036854775807)
		return (znak(sign));
	return (number * sign);
}
