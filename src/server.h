#ifndef SERVER_H
#define SERVER_H

#include "socket.h"

class Server: public Socket
{
public:
  void serverLoop();
  void serverRespondLoop(int socketKey);
};

#endif
