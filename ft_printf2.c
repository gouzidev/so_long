/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:45:20 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/03 22:45:21 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_putchar(char c, int *i)
{
	write(1, &c, 1);
	(*i)++;
}

void	ft_putstr(char *s, int *i)
{
	if (s == NULL)
	{
		write(1, "(null)", 6);
		*i += 6;
		return ;
	}
	while (*s)
	{
		write(1, s, 1);
		(*i)++;
		s++;
	}
}

void	ft_putaddr(void *p, int *i)
{
	unsigned long	addr;
	char			*base;

	base = "0123456789abcdef";
	addr = (unsigned long)p;
	ft_putstr("0x", i);
	if (addr == 0)
		ft_putchar(base[addr % 16], i);
	if (addr > 0)
		ft_print_rec(addr, base, i);
}

void	ft_puthex(unsigned int n, char x, int *i)
{
	if (n == 0)
		ft_putchar('0', i);
	if (n > 0)
	{
		if (x == 'x')
			ft_print_rec(n, "0123456789abcdef", i);
		else
			ft_print_rec(n, "0123456789ABCDEF", i);
	}
}
