#ifndef CLIENT_H
#define CLIENT_H

#include "socket.h"

class Client: public Socket
{
public:
  void clientLoop();
};

#endif
