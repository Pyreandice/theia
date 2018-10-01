#include "./message.h"

#include <cstdlib>
#include <string>
#include <cstring>

#include <iostream>

Message::Message()
{

}

Message::Message(std::string buffer)
{
  int bufferSize = buffer.size();
  int bufferStart = 0;

  for(int bufferIndex = 0; bufferIndex < bufferSize; bufferIndex++)
  {
    if(buffer[bufferIndex] == ':')
    {
      std::string subBuffer = buffer.substr(bufferStart, bufferIndex - bufferStart - 1);

      int equal = subBuffer.find("=");
      std::string key = subBuffer.substr(0, equal);
      std::string value = subBuffer.substr(equal + 1);

      std::cout << key << " - " << value << std::endl;

      this->process(key, value);

      bufferStart = bufferIndex + 1;
    }
  }

  std::cout << this->timeCreated << std::endl;
}

Message::~Message()
{

}

void Message::process(std::string key, std::string value)
{
  if(key == "timeCreated")
  {
    this->timeCreated = value;
  }
  else if(key == "")
  {

  }
}

char * Message::toBuffer()
{
  int bufferSize = 0;
  bufferSize += std::string("timeCreated").size();
  bufferSize += (this->timeCreated).size();

  std::string bufferString = "";
  bufferString += "timeCreated=";
  bufferString += std::string(this->timeCreated);
  bufferString += ":";

  char buffer[bufferSize + 1] = "";
  strcpy(buffer, bufferString.c_str());

  return buffer;
}
