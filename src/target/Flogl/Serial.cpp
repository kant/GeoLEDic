#include "Serial.hpp"

void SerialFromKeyboard::handleKey(char c)
{
   m_input.push(c);
}

bool SerialFromKeyboard::available()
{
   return not m_input.empty();
}

char SerialFromKeyboard::read()
{
   char c = ' ';
   if (available())
   {
      c = m_input.front();
      m_input.pop();
   }
   return c;
}

void SerialFromKeyboard::println(const char* msg)
{
   printf("%s\n", msg);
}
void SerialFromKeyboard::print(char c)
{
   printf("%c", c);
}

SerialFromKeyboard Serial;
