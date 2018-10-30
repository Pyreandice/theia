#include "./socket.h"

//original libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

//c to c++ req
#include <cstdlib>
#include <cstring>

//custom libs
#include <iostream>
#include <time.h>
#include <sys/time.h>

Socket::Socket()
{
  this->parentSocket = socket(AF_INET, SOCK_STREAM, 0);

  if(this->parentSocket < 0)
  {
    this->error("ERROR opening socket");
  }

  bzero((char *) &this->serverAddress, sizeof(this->serverAddress));

  this->serverAddress.sin_family = AF_INET;
  this->serverAddress.sin_addr.s_addr = INADDR_ANY;
  this->serverAddress.sin_port = htons(this->getPortNumber());

  for(int z = 0;z < this->maxConnectionRequests;z++)
  {
    this->sockets[z] = -1;
  }
}

Socket::Socket(int bufferSize)
{
  this->bufferSize = bufferSize;
  this->parentSocket = socket(AF_INET, SOCK_STREAM, 0);

  if(this->parentSocket < 0)
  {
    this->error("ERROR opening socket");
  }

  bzero((char *) &this->serverAddress, sizeof(this->serverAddress));

  this->serverAddress.sin_family = AF_INET;
  this->serverAddress.sin_addr.s_addr = INADDR_ANY;
  this->serverAddress.sin_port = htons(this->getPortNumber());

  for(int z = 0;z < this->maxConnectionRequests;z++)
  {
    this->sockets[z] = -1;
  }
}

Socket::Socket(int bufferSize, int portNumber)
{
  this->bufferSize = bufferSize;
  this->portNumber = portNumber;
  this->parentSocket = socket(AF_INET, SOCK_STREAM, 0);

  if(this->parentSocket < 0)
  {
    this->error("ERROR opening socket");
  }

  bzero((char *) &this->serverAddress, sizeof(this->serverAddress));

  this->serverAddress.sin_family = AF_INET;
  this->serverAddress.sin_addr.s_addr = INADDR_ANY;
  this->serverAddress.sin_port = htons(this->getPortNumber());

  for(int z = 0;z < this->maxConnectionRequests;z++)
  {
    this->sockets[z] = -1;
  }
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
  socklen_t clientTypeLength = sizeof(this->getClientAddress());
  int acceptedSocket = ::accept(this->parentSocket, (struct sockaddr *) &this->clientAddress, &clientTypeLength);

  if(acceptedSocket < 0)
  {
    this->error("ERROR accepting queued socket");
  }

  this->sockets[this->getFirstEmptySocketSlot()] = acceptedSocket;

  std::cout << "accepted socket fd: " << acceptedSocket << std::endl;

  return acceptedSocket;
}

void Socket::read(int socket, char * message)
{
  if(::read(socket, message, this->bufferSize - 1) < 0)
  {
    this->error("ERROR reading from socket");
  }

  std::cout << "read in: " << message;
}

void Socket::write(int socket, char * message)
{
  if(::write(socket, message, this->bufferSize - 1) < 0)
  {
    this->error("ERROR writing to socket");
  }
}

int Socket::connect(int socket)
{
  socklen_t serverTypeLength = sizeof(this->getServerAddress());
  int connectedSocket = ::connect(socket, (struct sockaddr *) &this->serverAddress, serverTypeLength);

  if(connectedSocket < 0)
  {
    this->error("ERROR accepting queued socket");
  }

  this->sockets[this->getFirstEmptySocketSlot()] = connectedSocket;

  std::cout << "connected socket fd: " << connectedSocket << std::endl;
  return connectedSocket;
}

void Socket::close(int socket)
{
  if(::close(socket) < 0)
  {
    this->error("ERROR closing socket");
  }

  for(int z = 0;z < this->maxConnectionRequests;z++)
  {
    if(this->sockets[z] == socket)
    {
      this->sockets[z] = -1;
    }
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

int Socket::getFirstEmptySocketSlot()
{
  //"round robin" selection
  for(int z = 0;z < this->maxConnectionRequests;z++)
  {
    std::cout << "key: " << z << " , sockets[z]: " << this->sockets[z] << std::endl;

    // -1 = empty
    if(this->sockets[z] < 0)
    {
      return z;
    }
  }

  this->error("SOCKET ARRAY FULL");
}
