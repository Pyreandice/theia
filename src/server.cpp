#include "server.h"

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
#include <streambuf>

void Server::serverLoop()
{
  while(1)
  {
    std::cout << "waiting to accept connections" << std::endl;
    this->clientFileDescriptor = this->accept();
    std::cout << "accepted connection" << std::endl;

    pid_t pid = fork();

    //child
    if(pid == 0)
    {
      this->serverRespondLoop();
      break;
    }
  }
}

void Server::serverRespondLoop()
{
  char message[this->bufferSize];
  bool active = true;

  while(active)
  {
    bzero(message, this->bufferSize);
    this->read(this->clientFileDescriptor, message);

    std::cout << "message: " << message << std::endl;

    active = this->handleMessage(message);
  }
}


bool Server::handleMessage(char * message)
{
  // make sure the messageType is set
  if(* message == 0)
  {
    std ::cout << "closing connection" << std::endl;
    this->close(this->clientFileDescriptor);
    return false;
  }

  // [MESSAGE DEFINITIONS]
  // ------------------
  //  0 - REQUEST
  //  1 - RESPONSE
  char messageType = message[0];

  // ---------------------------------------------------------------------------
  // [KEY HANDSHAKE]
  // ---------------------------------------------------------------------------
  // (TO SERVER): HELLO
  //  - CLIENT WRITES HELLO TO SERVER
  //  - ARGS:
  //    - SPECIFIC PUBLIC KEY
  // (TO CLIENT): HELLO
  //  - SERVER RESPONDS WITH HELLO TO CLIENT
  //  - ARGS:
  //    - NEWLY CREATED PUBLIC KEY FOR THAT SPECIFIC CLIENT
  //  - REQUIREMENTS:
  //    - SERVER MUST GENERATE PRIVATE/PUBLIC KEY PAIR
  //    - SERVER MUST STORE PRIVATE/PUBLIC KEY PAIR IN MEMORY
  //    - SERVER MUST POCESS MEMORY ON A SOCKET TO SOCKET BASIS
  //    - SERVER AND CLIENT ARE REQUIRED TO USE ENCRYPTED MESSAGES FROM HERE ON

  // ---------------------------------------------------------------------------
  // [PRIVLEDGE ESCALATION]
  // ---------------------------------------------------------------------------
  // (TO SERVER): AUTH
  // - CLIENT WRITES AUTH TO SERVER
  // - ARGS:
  //    - VALUE OF AUTH LEVEL [256-bit key] => LEVEL [0-3]
  // (TO CLIENT): [SUCCESS/FAILURE]
  // - SERVER WRITES OPERATION RESULT TO CLIENT
  //    - FAILURE
  //    - SUCCESS

  // ---------------------------------------------------------------------------
  // [SET [VAR]]
  // ---------------------------------------------------------------------------
  // (TO SERVER): SET [VAR] [VALUE]
  // - CLIENT WRITES SET COMMAND TO SERVER
  // - ARGS:
  //    - VARIABLE NAME
  //    - VARIABLE VALUE
  //    - (VAR = "STATE"; VALUE = ?)
  //      - CLOSED
  //      - READY
  //      - WORKING
  // (TO CLIENT): [SUCCESS/FAILURE]
  // - SERVER WRITES OPERATION RESULT TO CLIENT
  //    - FAILURE [REASON]
  //    - SUCCESS

  // ---------------------------------------------------------------------------
  // [GET [VAR]]
  // ---------------------------------------------------------------------------
  // (TO SERVER): GET [VAR]
  // - CLIENT WRITES GET COMMAND TO SERVER
  // - ARGS:
  //    - VARIABLE NAME
  // (TO CLIENT): RETURN [VAR VALUE]
  // - SERVER WRITES RETURN TO CLIENT
  // - ARGS:
  //    - VAR VALUE

  // ---------------------------------------------------------------------------
  // [CLOSING CONNECTION]
  // ---------------------------------------------------------------------------
  // (TO CLIENT): GOODBYE
  // - SERVER WRITES GOODBYE TO CLIENT
  // (CLIENT ACTION):
  // - CLOSES CONNECTION
  // (SERVER AUTO CLOSES CONNECTION WHEN SOCKET DROPPED)

  // ---------------------------------------------------------------------------
  // [EXPORTING DATA]
  // ---------------------------------------------------------------------------
  // (TO CLIENT): EXPORT [EXPORTTYPE]
  // - SERVER WRITES EXPORT TO CLIENT
  // - ARGS:
  //    - EXPORTTYPE - TYPE OF EXPORT CLIENT SHOULD PERFORM
  // (CLIENT ACTION) POST REQUEST TO URL - https://curl.haxx.se/libcurl/c/http-post.html

  // ---------------------------------------------------------------------------
  // [IMPORTING DATA]
  // ---------------------------------------------------------------------------
  // (TO CLIENT): IMPORT [TYPE] []
  // - SERVER WRITES EXPORT TO CLIENT
  // - ARGS:
  //    - TYPE - TYPE OF EXPORT CLIENT SHOULD PERFORM

  std::string command = this->getSubString(message, 1, 12);

  std::cout << "command: " << command << std::endl;

  if(command == "HELLO")
  {
    //init local variables
    std::string fileName;
    std::string commandString;

    //generate key pair unique temp fileName
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    std::chrono::system_clock::duration dtn = tp.time_since_epoch();
    fileName = dtn.count();

    //generate key pair
    commandString = "ssh-keygen -t rsa -N "" -f /tmp/" + fileName + ".ppk";
    const char * keyGenCommand = commandString.c_str();
    system(keyGenCommand);
    keyGenCommand = NULL;
    delete keyGenCommand;

    //get private key into server memory
    std::ifstream privateKeyFile(fileName + ".ppk");
    privateKeyFile.seekg(0, std::ios::end);
    //this->privateKey.reserve(privateKeyFile.tellg());
    privateKeyFile.seekg(0, std::ios::beg);
    //this->privateKey.assign((std::istreambuf_iterator<char>(privateKeyFile)), std::istreambuf_iterator<char>());

    //get public key into server memory
    std::ifstream publicKeyFile(fileName + ".ppk.pub");
    publicKeyFile.seekg(0, std::ios::end);
    //this->publicKey.reserve(publicKeyFile.tellg());
    publicKeyFile.seekg(0, std::ios::beg);
    //this->publicKey.assign((std::istreambuf_iterator<char>(publicKeyFile)), std::istreambuf_iterator<char>());

    //remove generated key pair
    commandString = "rm /tmp/" + fileName + ".*";
    const char * rmTempFilesCommand = commandString.c_str();
    system(rmTempFilesCommand);
    rmTempFilesCommand = NULL;
    delete rmTempFilesCommand;

    //send HELLO back to client with generated public key
  }
  else if(command == "AUTH")
  {

  }
  else if(command == "SET")
  {

  }
  else if(command == "GET")
  {

  }
  else
  {
    //return FAILURE [reason="did not understand command"]
  }

  this->write(this->clientFileDescriptor, message);

  return true;
}

std::string Server::getSubString(const char * haystack, int start, int end)
{
  std::string output = "";

  for(int z = start;z <= end;z++)
  {
    std::cout << "haystack[z]: " << haystack[z] << std::endl;
    output = output + haystack[z];
  }

  return output;
}

void issueRequest(char * message)
{

}

void issueResponse(char * message)
{

}

void handleRequest(char * message)
{

}

void handleResponse(char * message)
{

}
