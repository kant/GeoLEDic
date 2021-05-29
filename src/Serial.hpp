#ifndef GEOLEDIC_SERIAL_HPP
#define GEOLEDIC_SERIAL_HPP

#include "flogl/Config.hpp"
#include <queue>

class SerialFromKeyboard: public flogl::Config::KeyboardHandler
{
public:
   bool available();
   char read();

   // flogl::Config::KeyboardHandler
   virtual void handleKey(char c);

   void println(const char* msg = "");
   void print(char c);
   
private:
   std::queue<char> m_input;
};

extern SerialFromKeyboard Serial;


#endif // GEOLEDIC_SERIAL_HPP
