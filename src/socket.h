#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include "./controlBoard.h"

class Socket
{
public:
  Socket();
  Socket(int bufferSize);
  Socket(int bufferSize, int portNumber);
  ~Socket();

  //getter/setters
  int getBufferSize();
  void setBufferSize(int bufferSize);
  int getPortNumber();
  void setPortNumber(int portNumber);
  struct sockaddr_in getServerAddress();
  void setServerAddress(struct sockaddr_in serverAddress);
  struct sockaddr_in getClientAddress();
  void setClientAddress(struct sockaddr_in clientAdress);

  //default socket operations
  void bind();
  void listen();
  int accept();
  void read(int socket, char * message);
  void write(int socket, char * message);
  void close(int socket);
  int connect(int socket);

  //custom socket operations
  void error(std::string message);
  void clearBuffer();
  void clearAddress();

  int bufferSize = 1024;
  int portNumber = 8000;
  int parentSocket;

  struct sockaddr_in serverAddress;
  struct sockaddr_in clientAddress;

  int childrenSocketsKey = 0;
  int const static maxConnectionRequests = 32;
  int childrenSockets[maxConnectionRequests];
  ControlBoard controlBoard;
};

#endif
