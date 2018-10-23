#include "./server.h"

int main()
{
  Server * socket = new Server();

  socket->bind();
  socket->listen();
  socket->serverLoop();

  return 0;
}
