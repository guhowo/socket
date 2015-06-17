#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "local_socket.h"


int main()
{
	int sockfd;
	socklen_t len = 0;
	struct sockaddr_un address;
	int result = 0;
	char ch = 'A';

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, SUN_PATH);

	len = sizeof(address);
	result = connect(sockfd, (struct sockaddr *)&address, len);

	if(-1 == result) {
		perror("oops: client!");
		return 1;
	}

	write(sockfd, &ch, 1);
	read(sockfd, &ch, 1);
	printf("char from server : %c\n", ch);
	close(sockfd);
	return 0;
}
