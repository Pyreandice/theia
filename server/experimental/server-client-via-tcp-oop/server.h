#ifndef SERVER_H
#define SERVER_H

#include "./Socket.h"

class Server
{
public:
  Server();
  ~Server();

private:
  Socket * socket;
};

#endif
