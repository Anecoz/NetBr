#include <iostream>

#include "UDPClient.h"

int main()
{
  UDPClient client("localhost", 62553);
  client.sendMessage("hello world");

  int i;
  std::cin >> i;
  return 0;
}

