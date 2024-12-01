/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:34:41 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/05 17:59:30 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

int	ends_with(char *s, char *end)
{
	int	i;
	int	j;
	int	good;

	i = 0;
	good = 0;
	while (s[i])
	{
		j = 0;
		if (s[i] == end[j])
		{
			while (s[i] == end[j])
			{
				i++;
				j++;
				if (s[i] == '\0' && end[j] == '\0')
					return (1);
			}
		}
		else
			i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*output;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	output = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (output == NULL)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		output[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
		output[i++] = s2[j++];
	output[i] = '\0';
	return (output);
}

int	ft_sub_strlen(char *s, char c)
{
	int	i;

	i = 0;
	while (*s != c)
	{
		s++;
	}
	while (*s == c)
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strdup_len_nonl(const char *s1, int len)
{
	int		i;
	char	*buf;

	if (s1 == NULL)
		return (NULL);
	buf = malloc((len + 1) * sizeof(char));
	if (buf == 0)
		return (0);
	i = -1;
	while (++i < len)
		buf[i] = s1[i];
	buf[i] = '\0';
	return (buf);
}
