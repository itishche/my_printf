/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:30:11 by itishche          #+#    #+#             */
/*   Updated: 2019/02/11 11:30:13 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

static	void	ft_null(char *s)
{
	s[0] = '(';
	s[1] = 'n';
	s[2] = 'u';
	s[3] = 'l';
	s[4] = 'l';
	s[5] = ')';
	s[6] = '\0';
}

int				bla(char *s, t_buff *p, t_flags *flag)
{
	char	*mas;
	int		k;
	int		i;

	k = flag->tochnost;
	mas = ft_strnew(flag->tochnost);
	i = 0;
	while (k-- && *s)
		mas[i++] = *s++;
	if (flag->width != 0)
		k = flag->width - flag->tochnost + k + 1;
	else
		k = 0;
	if (k == 0)
		return (ft_write_buff_and_free(p, mas));
	if (k < 0)
		k = 0;
	if (flag->minus == 0)
		return (ft_right_str_and_free(mas, p, k, flag));
	return (ft_left_str_and_free(mas, p, k));
}

int				bla_bla(char *s, t_buff *p, t_flags *flag)
{
	int	k;
	int	len;

	len = ft_strlen(s);
	k = flag->width - len;
	if (k <= 0)
		k = 0;
	if (flag->minus == 0)
		return (ft_right_str(s, p, k, flag));
	if (flag->minus == 1)
		return (ft_left_str(s, p, k));
	return (0);
}

int				ft_str(void *str, t_buff *p, t_flags *flag)
{
	char	*s;
	char	fnull[7];
	int		len;

	ft_null(fnull);
	if (str == NULL)
		s = fnull;
	else
	{
		s = (char *)str;
		len = ft_strlen(s);
		if (len == 0)
			return (space(p, flag->width));
	}
	if (flag->tochnost == 0 && flag->dot == 1 && flag->width == 0)
		return (0);
	if (flag->tochnost == 0 && flag->dot == 1 && flag->width != 0
		&& flag->zero == 0)
		return (space(p, flag->width));
	if (flag->tochnost == 0 && flag->dot == 1 && flag->width != 0
		&& flag->zero == 1)
		return (fzero(p, flag->width));
	(flag->dot == 1 && flag->tochnost != 0) ? bla(s, p, flag)
		: bla_bla(s, p, flag);
	return (0);
}
