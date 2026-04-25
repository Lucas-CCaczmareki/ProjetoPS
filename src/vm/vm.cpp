/*
VM:
controla tudo (ciclo fetch-decode-execute)
coordena CPU, memória, decoder e executor
é o orquestrador da execução do programa

CodeSegment = struct (array de bytes)
DataSegment = struct (dados)
Stack = struct (push/pop) --> botar stack em file separado se ficar enorme

while(true) {

  // usa o pc pra achar a linha binario atual, exemplo: 00000001 00000000 00000001 (ADD A, B)
  //- precisamos definir os opcodes e etc de cada operacao -> ver na doc do zilog z80 e se n tiver nd decente inventar e documentar
  std::string instructionLine = read_binary_line_with_pc() // nome só pra exemplificar - pensar direito dps

  Instruction currInstruction = Decoder.decodeInstruction(instructionLine);
  Executor.executeInstruction(currInstruction); // aqui dentro chama cpu, cpu atualiza flags e etc..

  updateInterfaceState(); // atualiza GUI
}
*/

#include "vm.h"
#include <iostream>

void VM::run()
{
  std::cout << "VM running\n";

  mem.write(0x0000, 0x42);
  uint8_t val = mem.read(0x0000);
  std::cout << "mem[0x0000] = " << (int)val << "\n";
}