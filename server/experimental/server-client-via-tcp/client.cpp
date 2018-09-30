//original libs
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
//c to c++ req
#include <cstdlib>
#include <cstring>
#include <unistd.h>
//requirement for resolving peer ip
#include <arpa/inet.h>
//custom libs
#include <iostream>
#include <time.h>

void error(const char * msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char * argv[])
{
  int socket_file_descriptor, port_number, n;
  struct sockaddr_in server_address;
  struct hostent * server;
  char buffer[256];

  if(argc < 3)
  {
    fprintf(stderr, "usage %s hostname port\n", argv[0]);
    exit(0);
  }

  port_number = atoi(argv[2]);
  socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

  if(socket_file_descriptor < 0)
  {
    error("ERROR opening socket");
  }

  server = gethostbyname(argv[1]);

  if(server == NULL)
  {
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }

  bzero((char *) &server_address, sizeof(server_address));
  server_address.sin_family = AF_INET;
  bcopy((char *) server->h_addr, (char *) &server_address.sin_addr.s_addr, server->h_length);
  server_address.sin_port = htons(port_number);

  if(connect(socket_file_descriptor, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
  {
    error("ERROR connecting");
  }

  while(1)
  {
    printf("Please enter the message: ");

    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    n = write(socket_file_descriptor, buffer, strlen(buffer));

    if(n < 0)
    {
      error("ERROR writing to socket");
    }

    bzero(buffer, 256);
    n = read(socket_file_descriptor, buffer, 255);

    if(n < 0)
    {
      error("ERROR reading from socket");
    }

    socklen_t server_address_type = sizeof(server_address);
    n = getpeername(socket_file_descriptor, (struct sockaddr *) &server_address, &server_address_type);

    if(n < 0)
    {
      error("ERROR getting peer name and port");
    }

    printf("Peer's IP address is: %s\n", inet_ntoa(server_address.sin_addr));
    printf("Peer's port is: %d\n", (int) ntohs(server_address.sin_port));

    printf("%s\n", buffer);
  }

  close(socket_file_descriptor);
  return 0;
}
