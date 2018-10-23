#include "server.h"

#include <iostream>
#include <unistd.h>

void Server::serverLoop()
{
  while(1)
  {
    std::cout << "waiting to accept connections" << std::endl;
    int socketKey = this->accept();
    std::cout << "accepted connection" << std::endl;

    pid_t pid = fork();

    //child
    if(pid == 0)
    {
      this->serverRespondLoop(socketKey);
      break;
    }
  }
}

void Server::serverRespondLoop(int socketKey)
{
  while(1)
  {
    char * message;
    message = new char[this->bufferSize];

    std::cout << "waiting for message from client" << std::endl;
    this->read(socketKey, message);
    std::cout << message;

    if(message[0] == '\0')
    {
      this->close(socketKey);
      std ::cout << "closing connection" << std::endl;
      break;
    }

    std::cout << "read message: " << message;
    std::cout << "writing to client" << std::endl;
    this->write(socketKey, message);
    std::cout << "wrote: " << message;
  }
}
