/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 11:04:53 by itishche          #+#    #+#             */
/*   Updated: 2019/02/20 14:39:36 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int		ft_flag_d(va_list ap, t_buff *p, t_flags *flag)
{
	if (flag->l == 0 && flag->ll == 0 &&
		flag->h == 0 && flag->hh == 0 && flag->j == 0 && flag->z == 0)
		return (check_int(p, flag, (long long int)(int)va_arg(ap, void*)));
	else if (flag->l == 1)
		return (check_int(p, flag, (long long int)(long int)va_arg(ap, void*)));
	else if (flag->j == 1 || flag->ll == 1)
		return (check_int(p, flag, (long long int)va_arg(ap, void*)));
	else if (flag->h == 1)
		return (check_int(p, flag, (short int)va_arg(ap, void*)));
	else if (flag->hh == 1)
		return (check_int(p, flag, (signed char)va_arg(ap, void*)));
	else if (flag->z == 1)
		return (check_int(p, flag, (size_t)va_arg(ap, void*)));
	return (0);
}

int		ft_flag_u(va_list ap, t_buff *p, t_flags *flag)
{
	if (flag->u == 1 && flag->l == 0 && flag->ll == 0 &&
		flag->h == 0 && flag->hh == 0 && flag->j == 0 && flag->z == 0)
		return (check_u(p, flag, (unsigned int)va_arg(ap, void*)));
	if ((flag->l == 1) || flag->big_u == 1)
		return (check_u(p, flag, (unsigned long)va_arg(ap, void*)));
	else if ((flag->ll == 1 || flag->j == 1))
		return (check_u(p, flag, (unsigned long long)va_arg(ap, void*)));
	else if (flag->h == 1)
		return (check_u(p, flag, (unsigned short int)va_arg(ap, void*)));
	else if (flag->hh == 1)
		return (check_u(p, flag, (unsigned char)va_arg(ap, void*)));
	return (0);
}

int		ft_flag_x(va_list ap, t_buff *p, t_flags *flag)
{
	if (flag->l == 0 && flag->ll == 0 &&
		flag->h == 0 && flag->hh == 0 && flag->j == 0 && flag->z == 0)
		return (check_x(p, flag, (unsigned int)va_arg(ap, void*)));
	else if (flag->l == 1)
		return (check_x(p, flag, (unsigned long int)va_arg(ap, void*)));
	else if (flag->ll == 1)
		return (check_x(p, flag, (unsigned long long int)va_arg(ap, void*)));
	else if (flag->h == 1)
		return (check_x(p, flag, (unsigned short int)va_arg(ap, void*)));
	else if (flag->hh == 1)
		return (check_x(p, flag, (unsigned char)va_arg(ap, void*)));
	else if (flag->j == 1)
		return (check_x(p, flag, (uintmax_t)va_arg(ap, void*)));
	return (0);
}

int		checkall(va_list ap, t_buff *p, t_flags *flag)
{
	if (flag->s == 1)
		return (ft_str(va_arg(ap, void*), p, flag));
	if (flag->c == 1)
		return (ft_char(va_arg(ap, void*), p, flag));
	if (flag->d == 1)
		return (ft_flag_d(ap, p, flag));
	if (flag->u == 1 || flag->big_u == 1)
		return (ft_flag_u(ap, p, flag));
	if (flag->o == 1)
		return (ft_o((long int)va_arg(ap, void*), p, flag));
	if (flag->x == 1 || flag->big_x == 1)
		return (ft_flag_x(ap, p, flag));
	if (flag->f == 1 && flag->big_l == 0)
		return (ft_float(va_arg(ap, double), p, flag));
	if (flag->f == 1 && flag->big_l == 1)
		return (ft_float((long double)va_arg(ap, double), p, flag));
	if (flag->p == 1)
		return (ft_ptr(va_arg(ap, unsigned long int), p, flag));
	if (flag->percent == 1)
	{
		if (flag->tochnost == 0 && flag->dot == 1)
			flag->tochnost = 1;
		return (ft_str("%", p, flag));
	}
	return (0);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	t_buff	p;

	va_start(ap, format);
	p.i = 0;
	p.count = 0;
	while (*format)
	{
		if (*format != '%')
			p.buff[p.i++] = *format;
		else
			format += checkstr(ap, (char *)format, &p);
		format++;
		checkbuff(&p);
	}
	p.buff[p.i] = '\0';
	va_end(ap);
	p.count += p.i;
	write(1, p.buff, p.i);
	return (p.count);
}
