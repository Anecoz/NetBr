#pragma once

#include <string>

#include <boost/asio.hpp>
#include <boost/array.hpp>

class UDPServer
{
public:
  UDPServer() = delete;
  UDPServer(unsigned port);
  ~UDPServer();

private:
  void startReceive();
  void handleReceive(const boost::system::error_code& error,
                     std::size_t bytesTransferred);

  unsigned _port;
  boost::asio::io_service _ioService;
  boost::asio::ip::udp::socket _socket;  
  boost::asio::ip::udp::endpoint _remoteEndpoint;
  boost::array<char, 256> _recvBuffer;
};

