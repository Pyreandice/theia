#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include "./message.h"

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
  void init();
  void bind();
  void listen();
  int accept();
  Message read(int socket);
  void write(int socket, Message message);
  void close(int socket);

  //custom socket operations
  void error(std::string message);
  void clearBuffer();
  void clearAddress();
  void serverLoop();
  void clientLoop(int socketKey);

private:
  int bufferSize = 1024;
  int portNumber = 8080;
  int parentSocket;

  struct sockaddr_in serverAddress;
  struct sockaddr_in clientAddress;

  int childrenSocketsKey = 0;
  int const static maxConnectionRequests = 32;
  int childrenSockets[maxConnectionRequests];
};

#endif
