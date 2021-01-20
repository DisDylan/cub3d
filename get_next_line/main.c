#include "get_next_line.h"

int main(int argc, char **argv)
{
	int i;
	int j;
	char *line;
	int fd;
	int k;

	i = 0;
	j = 0;
	fd = open("../map/map.cub", O_RDONLY);
	while ((k = get_next_line(fd, &line)) == 1)
		i++;
	close(fd);
	fd = open("../map/map.cub", O_RDONLY);
	while ((k = get_next_line(fd, &line)) == 1)
		j++;
	printf("%d\n", i);
	printf("%d\n", j);
}
