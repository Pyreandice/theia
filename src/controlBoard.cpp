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
void ControlBoard::handleResponse(char * message)
{
  char * operation = std::strtok(message, " ");

  if(operation == "LOGIN")
  {
    operation = std::strtok(NULL, " ");

    int memoryStage = std::stoi(operation);

    if(memoryStage >= 0 && memoryStage < this->memoryStages)
    {
      //test if user is valid
      operation = std::strtok(NULL, " ");

      if(operation == this->memory[memoryStage][0])
      {
        return "";
      }
    }
  }

  if(operation == "LOGIN")
  {
    operation = std::strtok(NULL, " ");

    if(operation == "PROOF")
    {
      operation = std::strtok(NULL, " ");

      if(operation == std::getenv("SECRET"))
      {
        this->clients++;
        return "LOGIN SUCCESS " << (this->clients - 1);
      }
    }
    else if(operation == "SUCCESS")
    {
      operation = std::strtok(NULL, " ");


    }
  }

}
