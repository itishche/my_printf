/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itishche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:03:39 by itishche          #+#    #+#             */
/*   Updated: 2019/02/15 14:03:41 by itishche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

int		space(t_buff *p, int size)
{
	while (size--)
	{
		checkbuff(p);
		p->buff[p->i++] = ' ';
	}
	return (0);
}

int		ft_write_buff(t_buff *p, char *s)
{
	while (*s)
	{
		checkbuff(p);
		p->buff[p->i++] = *s;
		s++;
	}
	return (0);
}

char	*ft_strnew(size_t size)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * size + 1);
	if (ptr == 0)
		return (NULL);
	else
	{
		ft_bzero(ptr, size + 1);
		return (ptr);
	}
}
