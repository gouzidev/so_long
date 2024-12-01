/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:45:09 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/03 22:45:11 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	c_in_str(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	handler(va_list v, int *i, const char **s)
{
	if (*s && **s == '%')
	{
		if (c_in_str(*(*s + 1), "cidsupxX%"))
		{
			(*s)++;
			if (**s == 'c')
				ft_putchar(va_arg(v, int), i);
			if (**s == 's')
				ft_putstr(va_arg(v, char *), i);
			if (**s == 'd' || **s == 'i')
				ft_putint(va_arg(v, int), i);
			if (**s == 'u')
				ft_putunsigned(va_arg(v, unsigned int), i);
			if (**s == '%')
				ft_putchar('%', i);
			if (**s == 'p')
				ft_putaddr(va_arg(v, void *), i);
			if (**s == 'x' || **s == 'X')
				ft_puthex(va_arg(v, unsigned int), **s, i);
		}
	}
	else if (*s && **s)
		ft_putchar(**s, i);
}

int	ft_printf(const char *s, ...)
{
	va_list	v;
	int		i;

	va_start(v, s);
	i = 0;
	while (*s)
	{
		handler(v, &i, &s);
		s++;
	}
	va_end(v);
	return (i);
}
