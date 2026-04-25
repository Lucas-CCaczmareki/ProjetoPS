#pragma once
#include <cstdint>

class Memory
{
public:
  uint8_t read(uint16_t addr) const;
  void    write(uint16_t addr, uint8_t value);

private:
  uint8_t data[65536] = {};
};
