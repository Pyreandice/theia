#ifndef CONTROLBOARD_H
#define CONTROLBOARD_H

#include <iostream>

class ControlBoard
{
public:
  ControlBoard();
  ~ControlBoard();

  std::string * operations;
  std::string ** memory;
  std::string ** clients;
  int maxClients = 128;
  int memoryStages = maxClients;
  int memorySize = 256;

  std::string handleResponse(std::string message);
private:

};

#endif
