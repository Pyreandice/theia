#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message
{
public:
  Message();
  Message(std::string buffer);
  ~Message();

  void process(std::string key, std::string value);
  char * toBuffer();

private:
  char delimiter = ':';
  std::string timeCreated;
};

#endif
