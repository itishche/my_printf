/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:22:57 by itishche          #+#    #+#             */
/*   Updated: 2019/03/01 10:22:59 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

char		*ft_itoa_base(uintmax_t value, int base, t_flags *flag)
{
	int			sign;
	char		*str;
	int			i;
	uintmax_t	temp;

	sign = 0;
	i = 1;
	temp = value;
	while (temp /= base)
		i++;
	if (flag->hash == 1 && flag->o == 1)
		sign = 1;
	str = (char*)malloc(sizeof(char) * (i + sign));
	str[i + sign] = '\0';
	while (i-- > 0)
	{
		str[i + sign] = (value % base) + (value % base > 9 ? 'a' - 10 : '0');
		value = value / base;
	}
	if (sign != 0)
		str[0] = '0';
	return (str);
}

void		ft_bzero(void *str, size_t n)
{
	size_t			i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)str;
	while (i < n)
	{
		s[i] = '\0';
		i++;
	}
}

static int	mini_check_flag(int *flag, char **car)
{
	*flag = 1;
	(*car)++;
	return (1);
}

int			checkflag(char **car, t_flags *flag)
{
	int		i;
	char	*s;

	i = 0;
	if ((s = ft_strchr("#0-+ ", **car)) == NULL)
		return (i);
	while (**car < 49 && **car >= 32 && (**car == ' ' || **car == '#'
		|| **car == '-' || **car == '+' || **car == '0'))
	{
		if (**car == '#')
			i += mini_check_flag(&flag->hash, car);
		else if (**car == ' ')
			i += mini_check_flag(&flag->space, car);
		else if (**car == '0')
			i += mini_check_flag(&flag->zero, car);
		else if (**car == '+')
			i += mini_check_flag(&flag->plus, car);
		else if (**car == '-')
			i += mini_check_flag(&flag->minus, car);
	}
	return (i);
}
