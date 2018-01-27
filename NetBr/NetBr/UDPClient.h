#pragma once

#include <string>

#include <boost/asio.hpp>

using namespace boost::asio::ip;

class UDPClient
{
public:
  UDPClient() = delete;
  UDPClient(const std::string& ip, unsigned port);
  ~UDPClient();

  void sendMessage(const std::string& msg);

private:
  std::string _ip;
  unsigned _port;

  boost::asio::io_context _ioContext;
  udp::endpoint _receiverEndpoint;  
  udp::socket _socket;
  udp::resolver _resolver;  
};

