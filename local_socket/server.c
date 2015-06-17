#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "local_socket.h"


#define CONNECTION_QUEUE_SIZE 5

int main()
{
	int server_fd, client_fd;
	socklen_t client_len = 0, server_len = 0;
	struct sockaddr_un server_addr, client_addr;

	/* remove any old sockets & create an unnamed socket */
	unlink("server_socket");
	server_fd = socket(AF_UNIX, SOCK_STREAM, 0);

	/* name the socket */
	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, SUN_PATH);
	server_len = sizeof(server_addr);
	bind(server_fd, (struct sockaddr *)&server_addr, server_len);

	/* create a connection queue and wait for clients */
	listen(server_fd, CONNECTION_QUEUE_SIZE);
	while(1) {
		char ch;
		printf("Waiting for client...\n");

		client_len = sizeof(client_addr);
		client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

		read(client_fd, &ch, 1);
		ch++;
		write(client_fd, &ch, 1);
		close(client_fd);
	}

	return 0;
}


