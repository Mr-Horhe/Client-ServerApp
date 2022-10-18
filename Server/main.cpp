
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

const int max_length = 1024;
std::string serverResponseMsg = "GET_DATA_ACK";
void clientHandlerThread(tcp::socket sock)
{
  try
  {
    for (;;)
    {
      char data[max_length];

      boost::system::error_code error;
      size_t length = sock.read_some(boost::asio::buffer(data), error);
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      std::cout << "Received from client: " << data << "\n\n";

      if(boost::asio::write(sock, boost::asio::buffer(serverResponseMsg)));
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}

class Server {
public:
  Server(boost::asio::io_context& io_context, ushort port) : servPort(port), 
                                                             connAcceptor(io_context, tcp::endpoint(tcp::v4(), servPort)), 
                                                             servSocket(io_context) 
                                                             {}
  ~Server() {};

  tcp::socket connHandler() {
    std::cout << "APEXPREDATOR (IT'S ME)" << std::endl;
    return connAcceptor.accept();
  }

private:
  ushort servPort;
  tcp::acceptor connAcceptor;
  tcp::socket servSocket;
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;

    Server serv(io_context, std::atoi(argv[1]));

    std::cout << "Bar Penis's server successfully started" << std::endl;

    for(;;) {
      std::thread(clientHandlerThread, serv.connHandler()).detach();  
    }

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
