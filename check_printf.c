/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 12:42:53 by itishche          #+#    #+#             */
/*   Updated: 2019/03/18 12:42:55 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	checkwidth(t_flags *flag, char **car, va_list ap)
{
	int		i;
	char	minicar[20];

	i = 0;
	if (**car == '*')
	{
		(*car)++;
		flag->width = va_arg(ap, int);
		if (flag->width < 0)
		{
			flag->width *= -1;
			flag->minus = 1;
		}
		return (1);
	}
	while ((**car >= '0' && **car <= '9') || **car == ' ')
	{
		minicar[i++] = **car;
		(*car)++;
	}
	minicar[i] = '\0';
	flag->width = ft_atoi((const char*)minicar);
	return (i);
}

int	checktochnost(char **car, t_flags *flag, va_list ap)
{
	int		i;
	char	minicar[20];

	i = 0;
	if (**car == '.')
	{
		flag->dot = 1;
		(*car)++;
		if (**car == '*')
		{
			(*car)++;
			flag->tochnost = va_arg(ap, int);
			return (2);
		}
		minicar[i++] = ' ';
		while (**car >= '0' && **car <= '9')
		{
			minicar[i++] = **car;
			(*car)++;
		}
	}
	minicar[i] = '\0';
	flag->tochnost = ft_atoi(minicar);
	return (i);
}

int	checktype(t_flags *flag, char **car)
{
	int i;

	i = 0;
	flag->percent = (**car == '%') ? 1 : 0;
	flag->c = (**car == 'c') ? 1 : 0;
	flag->s = (**car == 's') ? 1 : 0;
	flag->d = (**car == 'd' || **car == 'i') ? 1 : 0;
	flag->o = (**car == 'o' || **car == 'O') ? 1 : 0;
	flag->u = (**car == 'u') ? 1 : 0;
	flag->big_u = (**car == 'U') ? 1 : 0;
	flag->big_x = (**car == 'X') ? 1 : 0;
	flag->x = (**car == 'x') ? 1 : 0;
	flag->f = (**car == 'f' || **car == 'F') ? 1 : 0;
	flag->p = (**car == 'p') ? 1 : 0;
	if (flag->percent == 0 && flag->c == 0 && flag->s == 0 && flag->d == 0
		&& flag->o == 0 && flag->u == 0 && flag->big_u == 0 && flag->big_x == 0
		&& flag->x == 0 && flag->f == 0 && flag->p == 0)
		flag->minwidth = 1;
	else
	{
		(*car)++;
		i = 1;
	}
	return (i);
}

int	checkmod(t_flags *flag, char **car, va_list ap, t_buff *p)
{
	int		i;
	char	*s;

	i = 0;
	flag->j = (**car == 'j') ? 1 : 0;
	flag->z = (**car == 'z') ? 1 : 0;
	flag->big_l = (**car == 'L') ? 1 : 0;
	flag->l = (**car == 'l') ? 1 : 0;
	flag->h = (**car == 'h') ? 1 : 0;
	if (flag->j == 1 || flag->z == 1 ||
		flag->big_l == 1 || flag->l == 1 || flag->h == 1)
	{
		(*car)++;
		flag->ll = (**car == 'l' && flag->l == 1) ? 1 : 0;
		flag->hh = (**car == 'h' && flag->h == 1) ? 1 : 0;
		flag->l = (flag->ll == 1) ? 0 : flag->l;
		flag->h = (flag->hh == 1) ? 0 : flag->h;
		i = (flag->hh == 1 || flag->ll == 1) ? 2 : 1;
		(flag->hh == 1 || flag->ll == 1) ? (*car)++ : 0;
	}
	return (i);
}

int	ft_minwidth(t_buff *p, char **car, t_flags *flag, int *k)
{
	char	s;
	int		i;
	int		c;

	c = *k;
	s = **car;
	if (flag->width == 0 || (flag->dot == 1 && flag->tochnost == 0
		&& flag->width == 0))
		return (c);
	i = flag->width - 1 < 0 ? 0 : flag->width - 1;
	(flag->minus == 0 && flag->zero == 0) ? space(p, i) : 0;
	(flag->minus == 0 && flag->zero == 1) ? fzero(p, i) : 0;
	p->buff[p->i++] = s;
	(*car)++;
	c++;
	(flag->minus == 1) ? space(p, i) : 0;
	return (c);
}
