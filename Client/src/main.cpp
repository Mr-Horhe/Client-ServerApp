#include <iostream>
#include <string>
#include <algorithm>
#include <thread>
#include <boost/asio.hpp>

#include "Client.h"

int main(int argc, char* argv[]) 
{
	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: ./main <host's ip> <host's port>" << std::endl;
			return 1;
		}

		boost::asio::io_context io_context;
		Client client(io_context, argv[1], std::atoi(argv[2]));
	
		std::thread sendThread([&client]() {client.sendThreadFunc();});
		std::thread receiveThread([&client]() {client.receiveThreadFunc();});

		if (sendThread.joinable())    sendThread.join();
		if (receiveThread.joinable()) receiveThread.join();

	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}