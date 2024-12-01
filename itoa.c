/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:34:29 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/03 01:34:30 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	count_digits(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

void	fill_rec(int n, char *buff, int *i)
{
	if (n > 0)
	{
		fill_rec(n / 10, buff, i);
		buff[*i] = (n % 10) + 48;
		*i = *i + 1;
	}
}

int	ft_handle(int i, char *buff, int n)
{
	char	*max;

	max = "-2147483648";
	if (n == -2147483648)
	{
		while (max[i])
		{
			buff[i] = max[i];
			i++;
		}
		return (1);
	}
	if (n == 0)
	{
		buff[0] = '0';
		return (1);
	}
	return (0);
}

char	*ft_itoa(int n)
{
	char	*buff;
	int		digit_len;
	int		i;

	digit_len = count_digits(n);
	buff = malloc((digit_len + 1) * sizeof(char));
	if (buff == 0)
		return (0);
	buff[digit_len] = '\0';
	i = 0;
	if (ft_handle(i, buff, n) == 1)
		return (buff);
	if (n < 0)
	{
		buff[i] = '-';
		i++;
		n = -n;
	}
	if (n > 0)
		fill_rec(n, buff, &i);
	return (buff);
}
