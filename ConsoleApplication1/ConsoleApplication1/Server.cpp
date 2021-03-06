#include "pch.h"
#include <SDL.h>
#include <SDL_net.h>
#include <cstring>
#include <string>
#include <iostream>

int main(int argc, char**argv)
{
	SDLNet_Init();
	//the text to be sent
	
	std::cout << "Enter Message:\n" << std::endl;
	std::string input;
	std::getline(std::cin, input);
	const char* text = input.c_str();
	IPaddress ip;
	//Gets the port
	int port;
	std::cout << "Enter Port:\n" << std::endl;
	std::cin >> port;
	//Since the IP is set to null it knows that it will be a server
	SDLNet_ResolveHost(&ip, NULL, port);
	//Opens a tcp sockent on the port 1337 as a server
	TCPsocket server = SDLNet_TCP_Open(&ip);
	std::cout << "Opening TCP socket on port: " <<port<<"\nWaiting for client...\n"<< std::endl;
	TCPsocket client;

	
	bool noClient = true;
	while (noClient)
	{
		//waits for a client to connect
		client = SDLNet_TCP_Accept(server);
		if (client)
		{
			//sends the text to the client
			SDLNet_TCP_Send(client, text, strlen(text) + 1);
			std::cout << "Packet Sent\n"<<std::endl;
			//Closes the connection
			SDLNet_TCP_Close(client);
			noClient = false;
		}
	}
	//Closes the socket
	SDLNet_TCP_Close(server);

	SDLNet_Quit();
	return 0;
}
