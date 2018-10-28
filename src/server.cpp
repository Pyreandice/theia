#include "server.h"

#include <iostream>
#include <unistd.h>
#include <cstring>


void Server::serverLoop()
{
  while(1)
  {
    std::cout << "waiting to accept connections" << std::endl;
    this->clientFileDescriptor = this->accept();
    std::cout << "accepted connection" << std::endl;

    pid_t pid = fork();

    //child
    if(pid == 0)
    {
      this->serverRespondLoop();
      break;
    }
  }
}

void Server::serverRespondLoop()
{
  char message[this->bufferSize];
  bool active = true;

  while(active)
  {
    bzero(message, this->bufferSize);
    this->read(this->clientFileDescriptor, message);

    std::cout << "message: " << message << std::endl;

    active = this->handleMessage(message);
  }
}


bool Server::handleMessage(char * message)
{
  // \0 - initialized
  //  0 - request
  //  1 - response
  // char messageType = message[0];

  std::cout << "message: " << message << std::endl;

  // make sure the messageType is set
  if(* message == 0)
  {
    std ::cout << "closing connection" << std::endl;
    this->close(this->clientFileDescriptor);
    return false;
  }

  char messageType = message[0];
  std::string operation = this->getSubString(message, 1, 12);

  std::cout << "operation: " << operation << std::endl;

  this->write(this->clientFileDescriptor, message);

  return true;
}

std::string Server::getSubString(const char * haystack, int start, int end)
{
  std::string output = "";

  for(int z = start;z <= end;z++)
  {
    std::cout << "haystack[z]: " << haystack[z] << std::endl;
    output = output + haystack[z];
  }

  return output;
}

void issueRequest(char * message)
{

}

void issueResponse(char * message)
{

}

void handleRequest(char * message)
{

}

void handleResponse(char * message)
{

}
