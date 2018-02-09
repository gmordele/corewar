#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include "libft.h"

typedef struct	s_data
{

}				t_data;

void err_exit(t_data data)
{
	(void)data;
	exit(EXIT_FAILURE);
}

void err_exit_str(char *str, t_data data)
{
	ft_dprintf(2, "error: %s\n", str);
	err_exit(data);
}

void err_exit_strerror(char *str, t_data data)
{
	ft_dprintf(2, "error: %s: %s\n", str, strerror(errno));
	err_exit(data);
}

long	get_filed_size(int fd, t_data data)
{
	long	size;

	if ((size = lseek(fd, 0, SEEK_END)) < 0)
		err_exit_strerror("lseek()", data);
	if (lseek(fd, 0, SEEK_SET) < 0)
		err_exit_strerror("lseek()", data);
	return (size);
}

#define MAX_FILE_SIZE 10000

char	*get_file_content(char *file, t_data data)
{
	long	size;
	int		fd;
	char	*content;

	if ((fd = open(file, O_RDONLY)) < 0)
		err_exit_strerror("open()", data);
	size = get_filed_size(fd, data);
	if (size <= 0 || size > MAX_FILE_SIZE)
		err_exit_str("bad file size", data);
	if ((content = (char *)malloc(size + 1)) == NULL)
		err_exit_strerror("malloc()", data);
	ft_bzero(content, size + 1);
	if ((read(fd, content, size)) < 0)
		err_exit_strerror("read()", data);
	close(fd);
	return (content);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_data data;
	
	if (argc < 2)
		err_exit_str("need argument", data);
	printf("%s\n", get_file_content(argv[1], data));

	return (0);
}
