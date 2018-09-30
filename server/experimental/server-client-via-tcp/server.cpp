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

void error(const char * msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char * argv[])
{
  int bufferSize = 1024;
  int socket_file_descriptor, new_socket_file_descriptor, port_number;
  socklen_t client_type_length;
  char buffer[bufferSize];
  struct sockaddr_in server_address, client_address;
  int n;

  if(argc < 2)
  {
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }

  socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

  if(socket_file_descriptor < 0)
  {
    error("ERROR opening socket");
  }

  bzero((char *) &server_address, sizeof(server_address));

  port_number = atoi(argv[1]);
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(port_number);

  if(bind(socket_file_descriptor, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)
  {
    error("ERROR on binding");
  }

  int max_connection_requests = 5;

  listen(socket_file_descriptor, max_connection_requests);
  client_type_length = sizeof(client_address);

  new_socket_file_descriptor = accept(socket_file_descriptor, (struct sockaddr *) &client_address, &client_type_length);

  pid_t pid = fork();

  std::cout << "Post fork" << std::endl;

  if(pid == 0)
  {
    std::cout << "Child" << std::endl;

    while(1)
    {
      std::cout << "Child loop" << std::endl;
      //child process
      bzero(buffer, bufferSize);

      time_t current_time;
      current_time = time(NULL);
      n = read(new_socket_file_descriptor, buffer, bufferSize - 1);
      current_time = time(NULL) - current_time;
      printf("[READ COST]: (%f seconds).\n", current_time);

      if(n < 0)
      {
        error("ERROR reading from socket");
      }

      printf("Here is the message: %s", buffer);

      current_time = time(NULL);
      n = write(new_socket_file_descriptor, "I got your message", 18);
      current_time = time(NULL) - current_time;
      printf("[WRITE COST]: (%f seconds).\n", current_time);

      if(n < 0)
      {
        error("ERROR writing to socket");
      }
    }
  }
  else if(pid > 0)
  {
    std::cout << "Parent" << std::endl;
    //parent process
    //close(new_socket_file_descriptor);
  }
  else
  {
    error("ERROR fork failed");
  }

  if(new_socket_file_descriptor < 0)
  {
    error("ERROR on accept");
  }

  std::cout << "closing" << std::endl;

  close(new_socket_file_descriptor);
  close(socket_file_descriptor);
  return 0;
}
