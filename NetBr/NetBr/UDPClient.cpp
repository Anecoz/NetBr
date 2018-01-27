#include "UDPClient.h"

#include <iostream>

#include <boost/array.hpp>

/*boost::array<char, 256> recvBuf;
udp::endpoint senderEndpoint;
std::size_t len = _socket.receive_from(boost::asio::buffer(recvBuf), senderEndpoint);

std::cout << "Got data with len: " << len << std::endl;*/

UDPClient::UDPClient(const std::string& ip, unsigned port) :
  _ip(ip),
  _port(port),
  _ioContext(),
  _resolver(_ioContext),
  _socket(_ioContext)
{
  try
  {
    _receiverEndpoint = *_resolver.resolve(udp::v4(), _ip, std::to_string(_port)).begin();
    _socket.open(udp::v4());
  }
  catch (std::exception& e)
  {
    std::cerr << "UDPClient::UDPClient error: " << e.what() << std::endl;
  }
}

UDPClient::~UDPClient()
{
}

void UDPClient::sendMessage(const std::string& msg)
{
  try
  {
    boost::array<char, 256> sendBuf;
    memcpy(sendBuf.elems, msg.data(), msg.size());
    _socket.send_to(boost::asio::buffer(sendBuf, msg.size()), _receiverEndpoint);
  }
  catch (std::exception& e)
  {
    std::cerr << "UDPClient::sendMessage error: " << e.what() << std::endl;
  }
}