#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

void test_file(const char *filename)
{
	int		fd;
	char	*line;
	int		i = 1;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("❌ Failed to open file: %s\n", filename);
		return;
	}
	printf("Reading file: %s\n", filename);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s", i++, line);
		free(line);
	}
	printf("End of file: %s\n\n", filename);
	close(fd);
}

void test_stdin(void)
{
	char	*line;
	int		i = 1;

	printf("⌨️  Enter text (Ctrl + D to end):\n");
	while ((line = get_next_line(0)) != NULL)
	{
		printf("STDIN Line %d: %s", i++, line);
		free(line);
	}
	printf("End of STDIN\n\n");
}

int main(void)
{
	test_file("test1.txt");
	test_file("empty.txt");
	test_file("no_newline.txt");
	test_file("long_line.txt");
	test_stdin();
	return (0);
}

