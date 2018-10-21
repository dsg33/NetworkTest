#include "pch.h"
#include <SDL.h>
#include <SDL_net.h>
#include <cstring>
#include <iostream>

int main(int argc, char**argv)
{
	SDLNet_Init();
	//the text to be sent
	char text[100];
	std::cout << "Enter Message:\n" << std::endl;
	std::cin >> text;
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
