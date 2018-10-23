#include "controlBoard.h"

#include <iostream>
#include <cstring>
#include <string>

#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

ControlBoard::ControlBoard()
{
  this->operations = new std::string[2];
  this->operations[0] = "GET";
  this->operations[1] = "SET";

  this->memory = new std::string * [this->memoryStages];
  for(int z = 0;z < this->memoryStages;z++)
  {
    this->memory[z] = new std::string[this->memorySize];

    for(int y = 0;y < this->memorySize;z++)
    {
      this->memory[z][y] = "";
    }
  }

  this->clients = new std::string * [this->maxClients];
}

ControlBoard::~ControlBoard()
{
  this->operations = NULL;
  delete this->operations;

  this->memory = NULL;
  delete this->memory;
}

void ControlBoard::handleClientResponse(char * message)
{

}

void ControlBoard::handleServerResponse(char * message)
{
  char * operation = std::strtok(message, " ");

  if(operation == "HELLO")
  {
    operation = std::strtok(NULL, " ");

    int memoryStage = std::stoi(operation);
  }
}
