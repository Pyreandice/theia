#include "./socket.h"

int main()
{
  Socket socket;

  socket.init();
  socket.bind();
  socket.listen();
  socket.serverLoop();

  return 0;
}
