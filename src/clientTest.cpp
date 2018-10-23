#include "client.h"

int main()
{
  Client * socket = new Client();
  socket->clientLoop();
}
