#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>
#include <thread>
#include "boost/asio.hpp"
#include "SharedBuffer.h"

class Client {
public:
	Client(boost::asio::io_context& io_context, std::string ipv4, ushort port) {
		socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context);
		socket->connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ipv4), port));
	};
	~Client() = default;

	void receiveThreadFunc();
	void sendThreadFunc();
private:
    std::shared_ptr<boost::asio::ip::tcp::socket> socket;
	boost::asio::streambuf receive_buffer;
	// socket
	// streambuf
	// io context
	sharedBuff<std::string> strBuffer;
};

#endif /* CLIENT_HPP */