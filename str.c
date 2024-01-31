#include "header.h"

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
		while (s[i] == end[j])
		{
			i++;
			j++;
			if (s[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}
void	verify_map_name(int ac, char *av[])
{
	// if (ac != 2)
	// 	print_exit("bad args count\n", 1);
	if (ends_with(av[1], ".ber") == 0)
		print_exit("bad map name\n", 1);
}
int	ft_istrlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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