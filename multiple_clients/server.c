/***************************************************
* file server.c
* process for multi-clients.
* The solution to this problem(fork()) is not good,
* it is better to user select()
****************************************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "multiple_socket.h"


int main()
{
	int server_sockfd,client_fd;
	struct sockaddr_in  server_addr, client_addr;
	socklen_t server_len, client_len;

	/* Create an unnamed socket for server */
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/* Name the socket */
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = SIN_PORT;
	server_addr.sin_addr.s_addr = inet_addr(LOOPBACK);
	server_len = sizeof(server_addr);
	bind(server_sockfd, (struct sockaddr *)&server_addr, server_len);

	/* Create a connection queue & wait for clients */
	listen(server_sockfd, SOCKET_QUEUE_SIZE);
	signal(SIGCHLD, SIG_IGN);

	while(1) {
		char ch;
		/* Accept a connection */
		client_len = sizeof(server_addr);
		client_fd = accept(server_sockfd, 
			(struct sockaddr *)&client_addr, &client_len);

		if(0 == fork()) {
			read(client_fd, &ch, 1);
			sleep(SLEEP_TIME);
			ch++;
			write(client_fd, &ch, 1);
			close(client_fd);
			exit(0);
		}
		else {
			close(client_fd);
		}
	}

	return 0;
}
