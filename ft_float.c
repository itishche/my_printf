/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 10:42:24 by itishche          #+#    #+#             */
/*   Updated: 2019/03/11 10:42:29 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

static	int	float_function(t_float *f, t_flags *flag)
{
	t_int	l;

	l.i = flag->tochnost;
	l.k = 0;
	while (l.k == 0)
		if (f->after[l.i] >= '5')
			while (l.k == 0 && l.i >= 0)
				if (f->after[l.i - 1] != '9')
				{
					if ((f->after[l.i - 1] - 48) % 2 != 0 || ((f->after[l.i - 1]
						- 48) % 2 == 0 && f->after[l.i] != '5'))
						f->after[l.i - 1] += 1;
					l.k = 1;
				}
				else
				{
					l.k = (l.i == 1 && f->after[0] == '9') ? 2 : 0;
					f->after[l.i-- - 1] = '0';
				}
		else
			l.k = 1;
	f->after[flag->tochnost] = '\0';
	return (l.k);
}

static void	round_f(t_flags *flag, t_float *f, long double c, t_buff *p)
{
	long int	i;
	long double	n;
	int			k;

	n = c - (long int)c;
	i = 0;
	f->after = ft_strnew(k);
	while (i < flag->tochnost + 1)
	{
		n = n * 10.0;
		f->after[i++] = (long int)n + 48;
		n = n - (long int)n;
	}
	i = (long int)c;
	if (flag->tochnost == 0 && flag->dot == 1)
	{
		if (f->after[0] >= '5' && (i % 2 != 0 ||
			(i % 2 == 0 && f->after[0] > '5')))
			i++;
		free(f->after);
	}
	else if ((k = float_function(f, flag)) == 2)
		i++;
	f->before = my_putnbr_int(i);
}

static int	ft_minus_zero(double i)
{
	long long *tmp;
	long long bitmove;
	long long j;

	tmp = (long long *)(&i);
	bitmove = *tmp;
	j = bitmove >> 63;
	if (j < 0)
		return (1);
	return (0);
}

static void	write_all_width_before_float(t_float *f, t_flags *flag, t_buff *p)
{
	f->kdigit = (flag->tochnost != 0) ? ft_strlen(f->before) +
	ft_strlen(f->after) + 1 : ft_strlen(f->before);
	if (flag->space == 1 && flag->plus == 0)
	{
		f->sign = (f->sign == '-') ? '-' : ' ';
		flag->plus = 1;
	}
	flag->zero = (flag->tochnost != 0) ? 0 : flag->zero;
	(flag->plus == 1 || f->sign == '-') ? flag->width-- : 0;
	f->k = (flag->width - f->kdigit < 0 ? 0 : flag->width - f->kdigit);
	if (flag->zero == 0)
	{
		(flag->minus == 0) ? space(p, f->k) : 0;
		if ((f->sign == '-' && flag->plus == 0) || (flag->plus == 1))
			p->buff[p->i++] = f->sign;
	}
	else
	{
		if ((f->sign == '-' && flag->plus == 0) || (flag->plus == 1))
			p->buff[p->i++] = f->sign;
		flag->minus == 0 ? fzero(p, f->k) : 0;
	}
}

int			ft_float(long double c, t_buff *p, t_flags *flag)
{
	t_float		f;

	f.i = (long int)c;
	f.sign = (f.i < 0 || ft_minus_zero(c) == 1) ? '-' : '+';
	c = (f.sign == '-') ? c * (-1.0) : c;
	flag->tochnost = (flag->dot == 0) ? 6 : flag->tochnost;
	round_f(flag, &f, c, p);
	write_all_width_before_float(&f, flag, p);
	ft_write_buff_and_free(p, f.before);
	(flag->tochnost == 0 && flag->hash == 1) ? ft_write_buff(p, ".") : 0;
	if (flag->tochnost != 0)
	{
		ft_write_buff(p, ".");
		ft_write_buff_and_free(p, f.after);
	}
	flag->minus == 1 ? space(p, f.k) : 0;
	return (0);
}
