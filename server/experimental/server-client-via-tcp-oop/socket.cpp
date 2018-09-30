#include "./server.h"
#include "./message.h"

//original libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//c to c++ req
#include <cstdlib>
#include <cstring>

//custom libs
#include <iostream>
#include <time.h>
#include <sys/time.h>

Socket::Socket()
{
  this->init();
}

Socket::~Socket()
{
  //this->close();
}

int Socket::getBufferSize()
{
  return this->bufferSize;
}

void Socket::setBufferSize(int bufferSize)
{
  this->bufferSize = bufferSize;
}

int Socket::getPortNumber()
{
  return this->portNumber;
}

struct sockaddr_in Socket::getServerAddress()
{
  return this->serverAddress;
}

void Socket::setServerAddress(struct sockaddr_in serverAddress)
{
  this->serverAddress = serverAddress;
}

struct sockaddr_in Socket::getClientAddress()
{
  return this->clientAddress;
}

void Socket::setClientAddress(struct sockaddr_in clientAddress)
{
  this->clientAddress = clientAddress;
}

void Socket::setPortNumber(int portNumber)
{
  this->portNumber = portNumber;
}

void Socket::init()
{
  this->parentSocket = socket(AF_INET, SOCK_STREAM, 0);

  if(this->parentSocket < 0)
  {
    error("ERROR opening socket");
  }

  bzero((char *) &this->serverAddress, sizeof(this->serverAddress));

  this->serverAddress.sin_family = AF_INET;
  this->serverAddress.sin_addr.s_addr = INADDR_ANY;
  this->serverAddress.sin_port = htons(this->getPortNumber());
}

void Socket::bind()
{
  if(::bind(this->parentSocket, (struct sockaddr *) &this->serverAddress, sizeof(this->serverAddress)) < 0)
  {
    this->error("ERROR binding socket");
  }
}

void Socket::listen()
{
  if(::listen(this->parentSocket, this->maxConnectionRequests) < 0)
  {
    this->error("ERROR listening to socket");
  }
}

int Socket::accept()
{
  int nextChildSocketKey = this->childrenSocketsKey;

  socklen_t clientTypeLength = sizeof(this->getClientAddress());
  this->childrenSockets[this->childrenSocketsKey] = ::accept(this->parentSocket, (struct sockaddr *) &this->clientAddress, &clientTypeLength);

  if(this->childrenSockets[this->childrenSocketsKey] < 0)
  {
    this->error("ERROR accepting queued socket");
  }

  this->childrenSocketsKey++;
  return this->childrenSockets[nextChildSocketKey];
}

Message Socket::read(int socket)
{
  char buffer[this->bufferSize];

  if(::read(socket, buffer, bufferSize - 1) < 0)
  {
    this->error("ERROR reading from socket");
  }

  std::string message = buffer;
  return Message(message);
}

void Socket::write(int socket, Message message)
{
  char test[128];
  char * buffer = test;

  if(::write(socket, buffer, sizeof(buffer)) < 0)
  {
    this->error("ERROR writing to socket");
  }
}

void Socket::close(int socket)
{
  if(::close(socket) < 0)
  {
    this->error("ERROR closing socket");
  }
}

void Socket::error(std::string message)
{
  char characters[message.size() + 1];
  strcpy(characters, message.c_str());
  perror(characters);
  exit(1);
}

void Socket::clearAddress()
{
  bzero((char *) &this->serverAddress, sizeof(this->serverAddress));
}

void Socket::serverLoop()
{
  while(1)
  {
    std::cout << "accepting connections" << std::endl;

    int socketKey = this->accept();

    std::cout << "accepted connection" << std::endl;

    pid_t pid = fork();

    //child
    if(pid == 0)
    {
      this->clientLoop(socketKey);
    }
  }
}

void Socket::clientLoop(int socketKey)
{
  while(1)
  {
    std::cout << "reading from client" << std::endl;
    Message message = this->read(socketKey);

    std::cout << "writing to client" << std::endl;
    this->write(socketKey, message);
  }
}
