#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int socket_desc, client_sock, c, read_size;
	struct sockaddr_in server, client;
	char client_message[2000];

	//creat socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1)
	{
		printf("could not creat socket");
	}
	puts("socket created");

	//prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	//bind
	if(bind(socket_desc, (struct socaddr *)&server, sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. error");
		return 1;
	}
	puts("bind done");

	//listen
	listen(socket_desc, 3);

	//accept and incoming connection
	puts("waiting for incoming connection....");
	c = sizeof(struct sockaddr_in);

	//accept connection from an incoming client
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
	if(client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	puts("connection accepted");

	//receive a message from client
	while((read_size = recv(client_sock, client_message, 2000, 0)) > 0)
	{
		//send the message back to client
		write(client_sock, client_message, strlen(client_message));
	}

	if(read_size == 0)
	{
		puts("client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}

	return 0;
}
