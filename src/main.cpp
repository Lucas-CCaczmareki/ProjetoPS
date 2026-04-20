#include <iostream>
#include "vm/vm.h"

int main()
{
    VM vm;
    vm.run();
    std::cout << "Hello World on main";
    return 0;
}