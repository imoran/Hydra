#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int		main(void)
{
	char	str[100];
	int		server_socket;
	int		connect;
	struct	sockaddr_in server_address;

	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("%s\n", "Socket() failed");
		return (1);
	}
	//why do we have to clear server_address??
	bzero(&server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htons(INADDR_ANY);
	server_address.sin_port = htons(22000);

	if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
	{
		printf("%s\n", "Bind failed");
		return (1);
	}
	//why do we have to specify maximum connection requests?
	listen(server_socket, 5);
	// int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
	// sockfd is our friendly neighborhood socket file descriptor, as returned by the socket() call, serv_addr is a struct sockaddr containing the destination port and IP address, and addrlen is the length in bytes of the server address structure.
	if ((connect = accept(server_socket, (struct sockaddr *)NULL, NULL)) < 0)
	{
		printf("%s\n", "Connect failed");
		return (1);
	}
	while (1)
	{
		bzero(str, 100);
		read(connect, str, 100);
		write(connect, str, strlen(str) + 1);
		write(connect, str, strlen(str) + 1);
		printf("%s", str);
	}
	// while (1)
	// {
	// 	write(connect, str, strlen(str + 1));
	// }
	close(server_socket);
	return (0);
}
