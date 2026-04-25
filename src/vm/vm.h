#pragma once
#include "../memory/memory.h"

class VM
{
public:
  void run();

private:
  Memory mem;
};