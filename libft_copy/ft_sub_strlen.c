#include "libft.h"

int ft_sub_strlen(char *s, char c)
{
	int i;

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