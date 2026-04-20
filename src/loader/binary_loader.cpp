/*
aqui a gente le um arquivo binario (.bin) contendo código JA montado pelo assembler

exemplo: [opcode][operand1][operand2]
ADD A, B  -> (assembler) -> 00000001 00000000 00000001

Loader: lê o .bin e coloca os 0s e 1s direto na memória da VM
*/