#include "./message.h"

#include <cstdlib>
#include <string>

Message::Message()
{

}

Message::Message(std::string buffer)
{
  int bufferSize = buffer.length();
  int bufferStart = 0;

  for(int bufferIndex = 0; bufferIndex < bufferSize; bufferIndex++)
  {
    if(bufferStart != bufferIndex)
    {
      if(buffer[bufferIndex] == ':')
      {
        int equal;
        std::string key = buffer.substr(0, buffer.find("=") - 1);
        std::string value = buffer.substr(equal + 1);

        this->process(key, value);
      }
    }
  }
}

Message::~Message()
{

}

void Message::process(std::string key, std::string value)
{
  if(key == "timeCreated")
  {
    this->timeCreated = (time_t) std::stoi(value);
  }
  else if(key == "")
  {

  }
}

char * Message::toBuffer()
{
  char buffer[128];
  buffer[0] = 'f';
  return buffer;
}
