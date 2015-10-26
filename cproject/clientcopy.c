#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in server;
	char message[1000], server_reply[2000];

	//creat socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		printf("Could not creat socket");
	}
	puts("Socket created");

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);

	//connct to remote server
	if(connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}

	puts("connected\n");

	//keep communicating with server
	while(1)
	{
		printf("Enter message : ");
		scanf("%s", message);

		//send some data
		if(send (sock, message, strlen(message), 0) < 0)
		{
			puts("send failed");
			return 1;
		}

		//receive a reply from the server
		if(recv(sock, server_reply, 2000, 0) < 0)
		{
			puts("recv failed");
			break;
		}

		puts("server reply : ");
		puts(server_reply);
	}

	close(sock);
	return 0;
}

