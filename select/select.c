/***************************************************
* file select.c
* program for select.
****************************************************/
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>


int main()
{
	char buffer[128];
	int result = 0, nread = 0;

	fd_set inputs, testfds;
	struct timeval timeout;

	FD_ZERO(&inputs);
	FD_SET(0, &inputs);

	while(1) {
		testfds = inputs;
		timeout.tv_sec = 2;
		timeout.tv_usec = 100;

		result = select(FD_SETSIZE, &testfds, 
			(fd_set *)NULL, (fd_set *)NULL, &timeout);
		switch(result) {
		case 0:
			printf("timeout!\n");
			break;
		case -1:
			perror("select");
			exit(1);
		default:
			memset((void *)buffer, 0, sizeof(buffer));
			nread = read(0, buffer, 127);
			buffer[nread] = 0;
			printf("read %d from keyboard: %s\n", nread, buffer);
			break;
		}
	}

	return 0;
}
