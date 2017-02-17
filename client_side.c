#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int		main(void)
{
	int		client_socket;
	char	send_line[100];
	char	receive_line[100];
	struct	sockaddr_in server_address;
	// int		x;

	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0) < 0))
		printf("%s\n", "socket() failed");
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(22000);

	inet_pton(AF_INET, "127.0.0.1", &(server_address.sin_addr));

	if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)))
	{
		printf("%s\n", "Connect failed");
		return (1);
	}
	while (1)
	{
		bzero(send_line, 100);
		bzero(receive_line, 100);
		fgets(send_line, 100, stdin);
		// printf("%d\n", client_socket);
		write(client_socket, send_line, strlen(send_line) + 1);
		// x = read(client_socket, receive_line, 100);
		read(client_socket, receive_line, 100);
		// printf("\n%d\n", x);
		printf("%s", receive_line);
	}
	return (0);
}
