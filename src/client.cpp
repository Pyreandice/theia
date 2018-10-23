#include "client.h"

#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

void Client::clientLoop()
{
  int socket = this->connect(this->parentSocket);

  while(1)
  {
    char buffer[this->bufferSize];

    printf("Please enter the message: ");

    bzero(buffer, this->bufferSize);
    fgets(buffer, this->bufferSize - 1, stdin);

    this->write(this->parentSocket, buffer);

    std::cout << "waiting to read from server" << std::endl;

    this->read(this->parentSocket, buffer);

    std::cout << buffer;

    socklen_t serverTypeLength = sizeof(this->getServerAddress());
    if(getpeername(this->parentSocket, (struct sockaddr *) &this->clientAddress, &serverTypeLength) < 0)
    {
      error("ERROR getting peer name and port");
    }

    printf("Peer's IP address: %s\n", inet_ntoa(this->serverAddress.sin_addr));
    printf("Peer's port: %d\n", (int) ntohs(this->serverAddress.sin_port));
    printf("Peer's message: %s\n", buffer);
  }
}
