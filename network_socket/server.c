#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "network_socket.h"

/**
 *
 * \brief
 *	Main processing of the server.
 *	When the normal end of the programme is carried out, it returns by 0.
 *
 * \param	none.
 *
 * \return	==0	Normal end
 * \return	!=0	Abnormal end
 *
 */
int main()
{
	int sockfd, client_sockfd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t server_len, client_len;

	/* create an unnamed socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/* Name the socket */
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = SIN_PORT;
	server_addr.sin_addr.s_addr = inet_addr(LOOPBACK);
	server_len = sizeof(server_addr);
	bind(sockfd, (struct sockaddr *)&server_addr, server_len);

	/* Create a connection queue and wait for clients */
	listen(sockfd, SOCKET_QUEUE_SIZE);

	while(1) {
		char ch;
		printf("Server wait...\n");
		/* Accept a connection */
		client_len = sizeof(client_addr);
		client_sockfd = accept(sockfd, 
			(struct sockaddr *)&client_addr, &client_len);

		read(client_sockfd, &ch, 1);
		ch++;
		write(client_sockfd, &ch, 1);
		close(client_sockfd);
	}

	return 0;
}