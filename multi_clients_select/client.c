/****************************************
* file server.c
* process for client.
*****************************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "multi_clients_select.h"

int main()
{
	int sockfd;
	struct sockaddr_in address;
	socklen_t len;
	int result;
	char ch = 'A';

	/* Create an unnamed socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	printf("client fd = %d\n", sockfd);

	/* Name the socket, as agreed with the server */
	address.sin_family = AF_INET;
	address.sin_port = htons(SIN_PORT);
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	len = sizeof(address);

	/* Connect your socket to the server’s socket */
	result = connect(sockfd, (struct sockaddr *)&address, len);

	if(-1 == result) {
		perror("Oops : client!");
		return -1;
	}

	write(sockfd, &ch, 1);
	read(sockfd, &ch, 1);
	printf("%c\n", ch);
	
	close(sockfd);

	return 0;
}
