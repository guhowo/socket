/***************************************************
* file server.c
* program for multi-clients.
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
#include <sys/time.h>
#include <sys/ioctl.h>
#include "multi_clients_select.h"


int main()
{
	int server_sockfd = 0, client_sockfd = 0;
	socklen_t server_len = 0, client_len = 0;
	struct sockaddr_in server_addr = {0};
	struct sockaddr_in client_addr = {0};
	int result = 0;
	int nread = 0;
	fd_set read_fds, test_fds;

	/* Create an unnamed socket */
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/* Name the socket */
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SIN_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_len = sizeof(server_addr);
	bind(server_sockfd, (struct sockaddr *)&server_addr, server_len);

	/* Create a socket queue for client to connect */
	listen(server_sockfd, SOCKET_QUEUE_SIZE);

	FD_ZERO(&read_fds);
	FD_SET(server_sockfd, &read_fds);
	client_len = sizeof(client_addr);

	while(1) {
		char ch;
		int fd;
		test_fds = read_fds;

		result = select(FD_SETSIZE, &test_fds, 
			(fd_set *)NULL, (fd_set *)NULL, (struct timeval *)NULL);
		
		if(result < 1) {
			perror("server");
			exit(1);
		}

		for(fd = 0; fd < FD_SETSIZE; fd++) {
			if(FD_ISSET(fd, &test_fds)) {
				if(fd == server_sockfd) {
					client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &client_len);
					FD_SET(client_sockfd, &read_fds);
					printf("add a client socket on fd: %d\n", client_sockfd);
				}
				else {
					ioctl(fd, FIONREAD, &nread);

					if(0 == nread) {
						close(fd);
						FD_CLR(fd, &read_fds);
					}
					else {
						read(fd, &ch, 1);
						sleep(SLEEP_TIME);
						ch++;
						write(fd, &ch, 1);
					}
				}
			}
		}
	}

	return 0;
}
