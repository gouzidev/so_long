/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 01:34:49 by sgouzi            #+#    #+#             */
/*   Updated: 2024/03/03 02:01:58 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	we_have_a_problem(int fd, char **str)
{
	if (fd < 0 || read(fd, 0, 0) < 0)
	{
		if (str)
		{
			free(*str);
			*str = NULL;
		}
		return (1);
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*buf;

	len = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[len])
		len++;
	buf = malloc((len + 1) * sizeof(char));
	if (buf == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		buf[i] = s1[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;
	char		*buff;
	int			bytes;

	if (we_have_a_problem(fd, &str))
		return (NULL);
	buff = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (free(buff), free(str), NULL);
	bytes = 1;
	while (!ft_strchr(str, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buff), free(str), NULL);
		buff[bytes] = '\0';
		str = ft_gnl_strjoin(str, buff);
	}
	free(buff);
	if (!str)
		return (free(str), NULL);
	line = ft_get_line(str);
	str = get_rest(str);
	return (line);
}

char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] && str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (free(str), NULL);
	i = -1;
	while (++i >= 0 && str[i] && str[i] != '\n')
		line[i] = str[i];
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_rest(char *str)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	buff = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!buff)
		return (free(buff), free(str), NULL);
	i++;
	j = 0;
	while (str[i])
		buff[j++] = str[i++];
	buff[j] = '\0';
	free(str);
	return (buff);
}
