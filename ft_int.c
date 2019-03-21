/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:08:07 by itishche          #+#    #+#             */
/*   Updated: 2019/02/21 10:08:10 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

static int	number_of_digits(long long int n)
{
	int				count;
	long long int	n2;

	count = 0;
	if (n == -9223372036854775807 - 1)
	{
		count++;
		n2 = 922337203685477580;
	}
	else
		n2 = ((n < 0) ? (n * (-1)) : n);
	while (n2 / 10 > 0)
	{
		count++;
		n2 = n2 / 10;
	}
	return (count + 1);
}

char		*my_putnbr_int(long long int n)
{
	int				sign;
	char			*s;
	int				i;
	long long int	n2;

	sign = ((n < 0) ? '-' : '+');
	i = number_of_digits(n);
	s = (char*)malloc(sizeof(char) * i + 1);
	s[i] = '\0';
	if (n == -9223372036854775807 - 1)
	{
		s[--i] = 8 + '0';
		n2 = 922337203685477580;
	}
	else
		n2 = (sign == '-' ? n * (-1) : n);
	while (i--)
	{
		s[i] = n2 % 10 + 48;
		n2 = n2 / 10;
	}
	return (s);
}

int			fzero(t_buff *p, int size)
{
	while (size--)
	{
		checkbuff(p);
		p->buff[p->i++] = '0';
	}
	return (0);
}

void		print_width_before_int(t_buff *p, t_flags *flag, t_float *l)
{
	if (flag->zero == 0)
	{
		if (flag->tochnost >= l->kdigit && flag->width >= flag->tochnost)
			l->k = l->k - (flag->tochnost - l->kdigit);
		if (flag->tochnost >= l->kdigit && flag->width < flag->tochnost)
			l->k = flag->tochnost - l->kdigit;
		else
			flag->minus == 0 ? space(p, l->k) : 0;
		if ((l->sign == '-' && flag->plus == 0) || (flag->plus == 1))
			p->buff[p->i++] = l->sign;
		if (flag->tochnost >= l->kdigit)
			fzero(p, flag->tochnost - l->kdigit);
	}
	else
	{
		if ((l->sign == '-' && flag->plus == 0) || (flag->plus == 1))
			p->buff[p->i++] = l->sign;
		if (flag->tochnost >= l->kdigit)
		{
			space(p, l->k - (flag->tochnost - l->kdigit));
			fzero(p, flag->tochnost - l->kdigit);
		}
		else
			flag->minus == 0 ? fzero(p, l->k) : 0;
	}
}

int			check_int(t_buff *p, t_flags *flag, long long int c)
{
	t_float	l;

	l.before = my_putnbr_int(c);
	l.sign = ((c < 0) ? '-' : '+');
	l.kdigit = ft_strlen(l.before);
	if (flag->zero == 1 && flag->dot == 1)
		flag->zero = 0;
	if (flag->space == 1 && flag->plus == 0)
	{
		l.sign = (l.sign == '-') ? '-' : ' ';
		flag->plus = 1;
	}
	(flag->plus == 1 || l.sign == '-') ? flag->width-- : 0;
	l.k = (flag->width - l.kdigit < 0 ? 0 : flag->width - l.kdigit);
	print_width_before_int(p, flag, &l);
	if (flag->tochnost == 0 && flag->dot == 1
		&& flag->width == 0 && l.before[0] == '0')
		l.before[0] = '\0';
	if (flag->tochnost == 0 && flag->dot == 1
		&& flag->width != 0 && l.before[0] == '0')
		l.before[0] = 32;
	ft_write_buff_and_free(p, l.before);
	flag->minus == 1 ? space(p, l.k) : 0;
	return (0);
}
