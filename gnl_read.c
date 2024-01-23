#include <unistd.h>
#include <fcntl.h>
#include "./gnl/get_next_line.h"
#include <stdio.h>

void print_map(char **map, int map_height)
{
    int i = 0;
    int j = 0;
    while (i < map_height)
    {
        j = 0;
        while (j < ft_strlen(map[i]))
        {
            write(1, &map[i][j], 1);
            j++;
        }
        write(1, "\n", 1);
        i++;
    }
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

int main(int ac, char *av[])
{
    char **map;
    int fd;
    int line_count;
    char *line;
    int line_len;
    if (ac != 2)
    {
        printf("provide a map please\n");
        exit(1);
    }
    fd = open(av[1], O_RDONLY);
    if (fd <= 0)
    {
        printf("problem reading the file\n");
        exit(1);
    }
    line = get_next_line(fd);
    line_count = 0;
    while (line)
    {
        line_count++;
        line = get_next_line(fd);
    }
    close(fd);
    fd = open(av[1], O_RDONLY);
    if (fd <= 0)
    {
        printf("problem reading the file\n");
        exit(1);
    }
    map = malloc((line_count + 1) * sizeof(char *));
    line = get_next_line(fd);
    line_count = 0;
    while (line)
    {
        line_len = ft_strlen_till(line, '\n');
        map[line_count] = ft_strdup_len_nonl(line, line_len);
        line_count++;
        line = get_next_line(fd);
    }
    line_len = ft_strlen(line);
    map[line_count] = ft_strdup_len_nonl(line, line_len);
    print_map(map, line_count);
    printf("there is %d lines in %s\n", line_count, av[1]);
}