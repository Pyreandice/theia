#ifndef SERVER_H
#define SERVER_H

#include "socket.h"

class Server: public Socket
{
public:
  void serverLoop();
  void serverRespondLoop();

  bool handleMessage(char * message);

  void issueRequest(char * message);
  void issueResponse(char * message);
  void handleRequest(char * message);
  void handleResponse(char * message);

  std::string getSubString(const char * haystack, int start, int end);

  int clientFileDescriptor;
};

#endif
