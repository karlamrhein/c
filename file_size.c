#if 0
	Determine file size by using open() and lseek()  --ksa
#endif

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char *argv[])
{

	int i;
	long j, file_size(char *file);

	for (i=1; i<argc; i++)
	{
		j = -1;
		j = file_size(argv[i]);
		if (j != -1)
		{
		    printf("%-20s: %20ld\n", argv[i], j);
		}
	}

	return(0);
}

long file_size(char *file)
{
	int fd;
	void err_msg(char *msg, char *file);
	long size;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		err_msg("open", file);
		return (-1);
	}

	if ((size = lseek(fd, 0, SEEK_END)) == -1)
	{
		err_msg("lseek", file);
		return (-1);
	}

	if (close(fd) == -1)
	{
		err_msg("close", file);
		exit(errno);
	}

	return(size);
}

void err_msg(char *msg, char *file)
{
	fprintf(stderr, "%s: %s: %s\n", msg, file, strerror(errno));
}
