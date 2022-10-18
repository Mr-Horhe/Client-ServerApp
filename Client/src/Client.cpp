#include "Client.h"

void Client::sendThreadFunc() {
	std::string str;
	for (;;) {
		while (true) {
			std::cout << "Input string: ";
			std::cin >> str;
			if (str.length() > 64);
			int count = 0;
			for (const auto& c : str) {
				if (c > 57 || c < 48)
				{
					count = 1;
					break;
				}
			}
			if (count > 0) continue;
			break;
		}
		for (int i = 0; i < str.length() - 1; i++) {
			for (int j = 0; j < str.length() - 1; j++) {
				if (str[j] < str[j + 1]) {
					std::swap(str[j], str[j + 1]);
				}
			}
		}
		for (int i = 0; i < str.length(); i++) {
			if (((str[i] - '0') % 2) == 0) {
				str[i] = 'K';
			}
		}
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == 'K') {
				str.insert(i + 1, "B");
			}
		}
		std::cout << "\nFirst thread id: " << std::this_thread::get_id() << std::endl;

		strBuffer.push(str);
	}
}

void Client::receiveThreadFunc() {
	std::string str;
	for (;;) {
		str = strBuffer.pull();

		std::cout << "\nSecond thread id: " << std::this_thread::get_id() << std::endl;
		int sum = 0;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] < 57 && str[i] > 48) {
				sum += str[i] - 48;
			}
		}

		boost::system::error_code error;
		std::string data;
		if(boost::asio::write(*socket, boost::asio::buffer(std::to_string(sum)))) {
      		size_t bytes_read = socket->read_some(boost::asio::buffer(data), error);
		} else {
			std::cerr << "Error: " << error << std::endl;
		}

		std::cout << "\nReceived from server: " << data << std::endl;
	}
}
