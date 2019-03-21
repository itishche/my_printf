/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_buff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 12:00:51 by itishche          #+#    #+#             */
/*   Updated: 2019/03/19 12:00:53 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	ft_write_buff_and_free(t_buff *p, char *s)
{
	ft_write_buff(p, s);
	free(s);
	return (0);
}

int	ft_left_str(char *mas, t_buff *p, int size)
{
	ft_write_buff(p, mas);
	space(p, size);
	return (0);
}

int	ft_right_str(char *mas, t_buff *p, int size, t_flags *flag)
{
	if (flag->zero == 1)
		fzero(p, size);
	else
		space(p, size);
	ft_write_buff(p, mas);
	return (0);
}

int	ft_left_str_and_free(char *mas, t_buff *p, int k)
{
	ft_left_str(mas, p, k);
	free(mas);
	return (0);
}

int	ft_right_str_and_free(char *mas, t_buff *p, int k, t_flags *flag)
{
	ft_right_str(mas, p, k, flag);
	free(mas);
	return (0);
}
