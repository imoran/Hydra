/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hydra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 12:45:43 by imoran            #+#    #+#             */
/*   Updated: 2017/02/16 12:45:47 by imoran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h> //for daemon
#include <sys/types.h>
#include <sys/socket.h> //for socket
#include <netinet/in.h> //contains struct to be able to give address/port to remote socket

int		main(void)
{
	int		network_socket;
	int		server_socket;
	int		client_socket;
	char	server_response[256];
	char	server_message[256];

	server_message = "You have reached the server";
	//creating client socket

	//domain of socket, since its internet, it needs to be AF_INET
	//sockstream is a tcp protocol socket (connection)
	//0 since we are using TCP default protocol.
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//specify address
	struct sockaddr_in network_address;
	struct sockaddr_in server_address;

	network_address.sin_family = AF_INET; //type of address
	server_address.sin_family = AF_INET;
	//specify port
	network_address.sin_port = htons(9002); //htons is conversion function to put in right network byte order
	//actual address
	server_address.sin_port = htons(9002);
	network_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_addr.s_addr = INADDR_ANY;

	int connection_stats = connect(network_socket, (struct sockaddr *)&network_address, sizeof(network_address));
	if (connection_stats == -1)
		printf("%s\n", "Something went wrong\n\n");
	//receiving data from network
	recv(network_socket, &network_response, sizeof(network_response), 0);
	printf("%s\n", network_response);

	bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
	listen(server_socket, 5);
	client_socket = accept(server_socket, NULL, NULL);

	send(client_socket, server_message, sizeof(server_message), 0);

	//close the socket
	close(network_socket);



	//creating the server socket


	return (0);
}
