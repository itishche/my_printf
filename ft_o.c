/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_o.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:30:08 by itishche          #+#    #+#             */
/*   Updated: 2019/03/01 10:30:10 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

static	int	poshuk(const char *str, int symb)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while ((k == 0) && (str[i] != '\0'))
	{
		if (str[i] == symb)
			k = 1;
		i++;
	}
	return (k);
}

char		*ft_strchr(const char *str, int symb)
{
	int i;
	int k;

	i = 0;
	if (symb == '\0')
		return ((char *)&str[ft_strlen((char*)str)]);
	k = poshuk(str, symb);
	if (k == 1)
	{
		i = 0;
		while (str[i] != symb)
			i++;
		return ((char *)&str[i]);
	}
	else
		return (0);
}

void		print_width_before_o(t_buff *p, t_flags *flag, t_float *l)
{
	if (flag->zero == 0)
	{
		if (flag->tochnost >= l->kdigit && flag->width >= flag->tochnost)
			l->k = flag->width - flag->tochnost;
		if (flag->tochnost >= l->kdigit && flag->width < flag->tochnost)
			l->k = flag->tochnost - l->kdigit;
		else
			flag->minus == 0 ? space(p, l->k) : 0;
		if (flag->tochnost >= l->kdigit)
		{
			fzero(p, flag->tochnost - l->kdigit);
			l->k = (flag->width >= flag->tochnost) ?
			flag->width - flag->tochnost : 0;
		}
	}
	else
	{
		if (flag->tochnost >= l->kdigit)
		{
			space(p, l->k - (flag->tochnost - l->kdigit));
			fzero(p, flag->tochnost - l->kdigit);
		}
		else
			flag->minus == 0 ? fzero(p, l->k) : 0;
	}
}

int			ft_o(long int c, t_buff *p, t_flags *flag)
{
	t_float	l;

	if (c == 0)
	{
		l.before = ft_strnew(1);
		l.before[0] = '0';
	}
	else
		l.before = ft_itoa_base((uintmax_t)c, 8, flag);
	l.kdigit = ft_strlen(l.before);
	if (flag->zero == 1 && flag->dot == 1)
		flag->zero = 0;
	l.k = (flag->width - l.kdigit < 0 ? 0 : flag->width - l.kdigit);
	print_width_before_o(p, flag, &l);
	if (flag->tochnost == 0 && flag->dot == 1
		&& flag->width == 0 && l.before[0] == '0' && flag->hash == 0)
		l.before[0] = '\0';
	if (flag->tochnost == 0 && flag->dot == 1 &&
		flag->width != 0 && l.before[0] == '0' && flag->hash == 0)
		l.before[0] = 32;
	ft_write_buff_and_free(p, l.before);
	flag->minus == 1 ? space(p, l.k) : 0;
	return (0);
}
