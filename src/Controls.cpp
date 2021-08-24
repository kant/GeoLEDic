#include "Controls.hpp"
#include <algorithm>

Controls::Controls()
{
   std::fill_n(m_control_values, sizeof(m_control_values), 0);
}

void Controls::controlChange(uint8_t cc_num, uint8_t value)
{
   if (cc_num >= sizeof(m_control_values)) return;
   m_control_values[cc_num] = value;
}

uint8_t Controls::getControlValue(uint8_t cc_num) const
{
   if (cc_num >= sizeof(m_control_values)) return 0;
   return m_control_values[cc_num];
}
