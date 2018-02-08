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

static err_exit(char *str, t_data data)
{
	(void)data;
	ft_dprintf(2, "%s\n", str);
	exit(EXIT_FAILURE);
}

static long	get_filed_size(int fd)
{
	long	size;

	if ((size = lseek(fd, 0, SEEK_END)) < 0)
		err_exit("error: lseek()\n");
	if (lseek(fd, 0, SEEK_SET) < 0)
		err_exit("error: lseek()\n");
	return (size);
}

int main(int argc, char **argv)
{
	

	return (0);
}
