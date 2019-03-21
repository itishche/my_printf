/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:12:21 by itishche          #+#    #+#             */
/*   Updated: 2019/03/12 13:12:26 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int			checkstr(va_list ap, char *car, t_buff *p)
{
	t_flags	flag;
	int		k;

	car++;
	k = 0;
	ft_bzero(&flag, sizeof(flag));
	k += checkflag(&car, &flag);
	k += checkwidth(&flag, &car, ap);
	k += checktochnost(&car, &flag, ap);
	k += checkmod(&flag, &car, ap, p);
	k += checktype(&flag, &car);
	if (flag.minwidth == 1)
		return (ft_minwidth(p, &car, &flag, &k));
	checkall(ap, p, &flag);
	return (k);
}

static int	number_of_digits(unsigned long long n)
{
	int count;

	count = 0;
	while (n / 10 > 0)
	{
		count++;
		n = n / 10;
	}
	return (count + 1);
}

char		*my_putnbr_u(unsigned long long n)
{
	int		sign;
	char	*s;
	int		i;

	i = number_of_digits(n);
	s = (char*)malloc(sizeof(char) * i + 1);
	s[i] = '\0';
	while (i--)
	{
		s[i] = n % 10 + 48;
		n = n / 10;
	}
	return (s);
}

void		print_width_before_u(t_buff *p, t_flags *flag, t_float *l)
{
	if (flag->zero == 0)
	{
		if (flag->tochnost >= l->kdigit && flag->width >= flag->tochnost)
			l->k = l->k - (flag->tochnost - l->kdigit);
		if (flag->tochnost >= l->kdigit && flag->width < flag->tochnost)
			l->k = flag->tochnost - l->kdigit;
		else
			flag->minus == 0 ? space(p, l->k) : 0;
		if (flag->tochnost >= l->kdigit)
			fzero(p, flag->tochnost - l->kdigit);
	}
	else
	{
		if (flag->plus == 1)
			p->buff[p->i++] = '+';
		if (flag->tochnost >= l->kdigit)
		{
			space(p, l->k - (flag->tochnost - l->kdigit));
			fzero(p, flag->tochnost - l->kdigit);
		}
		else
			flag->minus == 0 ? fzero(p, l->k) : 0;
	}
}

int			check_u(t_buff *p, t_flags *flag, unsigned long long c)
{
	char	*s;
	int		kdigit;
	int		k;
	t_float	l;

	l.before = my_putnbr_u(c);
	l.kdigit = ft_strlen(l.before);
	flag->plus == 1 ? flag->width-- : 0;
	if (flag->zero == 1 && flag->dot == 1)
		flag->zero = 0;
	l.k = (flag->width - l.kdigit < 0 ? 0 : flag->width - l.kdigit);
	print_width_before_u(p, flag, &l);
	if (flag->tochnost == 0 && flag->dot == 1 && flag->width == 0 &&
		l.before[0] == '0')
		l.before[0] = '\0';
	if (flag->tochnost == 0 && flag->dot == 1 && flag->width != 0 &&
		l.before[0] == '0')
		l.before[0] = ' ';
	ft_write_buff_and_free(p, l.before);
	flag->minus == 1 ? space(p, l.k) : 0;
	return (0);
}
