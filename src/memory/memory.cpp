#include "memory.h"

uint8_t Memory::read(uint16_t addr) const
{
  return data[addr];
}

void Memory::write(uint16_t addr, uint8_t value)
{
  data[addr] = value;
}
