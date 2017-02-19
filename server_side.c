/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_side.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:06:06 by imoran            #+#    #+#             */
/*   Updated: 2017/02/18 16:06:08 by imoran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

static void		daemonize(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid > 0)
		exit(1);
	if (setsid() < 0)
		exit(1);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
}

int				main(int argc, char **argv)
{
	char		str[100];
	int			server_socket;
	int			connect;
	struct		sockaddr_in server_addr;
	struct		sockaddr_in client_addr;
	socklen_t	client_len;

	if (argc == 2)
	{
		if (strcmp(argv[1], "-D") == 0)
			daemonize();
	}
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("%s\n", "Socket failed");
		return (1);
	}
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(22000);
	if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("%s\n", "Bind failed");
		return (1);
	}
	if (listen(server_socket, 5) < 0)
	{
		printf("%s\n", "Listen failed");
		return (1);
	}
	client_len = sizeof(client_addr);
	if ((connect = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) < 0)
	{
		printf("%s\n", "Connect failed");
		return (1);
	}
	while (1)
	{
		bzero(str, 100);
		if (read(connect, str, 100) < 0)
		{
			printf("%s\n", "Error reading from socket");
			return (1);
		}
		printf("%s", str);
		if (strcmp(str, "ping") == 13)
			strcpy(str, "pong\n");
		if (write(connect, str, strlen(str) + 1) < 0)
		{
			printf("%s\n", "Error writing to socket");
			return (1);
		}
		write(connect, str, strlen(str) + 1);
	}
	return (0);
}
