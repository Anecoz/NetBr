#include "UDPServer.h"

#include <iostream>
#include <boost/bind.hpp>

UDPServer::UDPServer(unsigned port) :
  _port(port),
  _ioService(),
  _socket(_ioService, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), _port))
{
  startReceive();
  _ioService.run();  
}

UDPServer::~UDPServer()
{}

void UDPServer::startReceive()
{
  _socket.async_receive_from(
    boost::asio::buffer(_recvBuffer),
    _remoteEndpoint,
    boost::bind(&UDPServer::handleReceive,
                this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
}

void UDPServer::handleReceive(const boost::system::error_code& error,
                              std::size_t bytesTransferred)
{
  std::string msg; // atm we know it's a string
  std::copy(_recvBuffer.begin(), _recvBuffer.begin() + bytesTransferred, std::back_inserter(msg));
  std::cout << "Received msg: " << msg << std::endl;
  startReceive();
}