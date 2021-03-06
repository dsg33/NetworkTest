#include "pch.h"
#include <SDL.h>
#include <SDL_net.h>
#include <cstring>
#include <string>
#include <iostream>

int main(int argc, char**argv)
{
	SDLNet_Init();

	IPaddress ip;
	//get ip and port
	std::cout << "Enter IP address:\n" << std::endl;
	std::string ipinput;
	std::getline(std::cin, ipinput);
	const char* input = ipinput.c_str();
	std::cout << "Enter Port:\n" << std::endl;
	int port;
	std::cin >> port;

	//find the host
	std::cout << "Connecting to: " << input << ":" << port << "\n" << std::endl;
	SDLNet_ResolveHost(&ip, input, port );
	
	//establish the connection
	TCPsocket client=NULL;
	//keeps trying to connect, client will stay null untill SDL net can open a connection with the defined ip
	while(client==NULL)
		client=SDLNet_TCP_Open(&ip);
	std::cout << "Connected\n" << std::endl;

	char text[100];
	//recieve and output the text that was sent
	//will return 0 when connection is closed
	while (SDLNet_TCP_Recv(client, text, 100))
		std::cout << text;
	SDL_Delay(5000);
	std::cout << "Closing connection...\n" << std::endl;
	SDLNet_TCP_Close(client);

	SDLNet_Quit();

	return 0;
}