# VM zilog Z80

## VM módulos:

- 1. Executor (Emulador): responsável pela execução das instruções Z80;
- 2. Interface Visual: exibição do estado dos registradores, memória e fluxo de execução.

## Memoria

- Barramento de endereços: 16 bits (2^16 endereços ~ 64 KB de memória)
- Barramento de dados: 8 bits (cpu le e escreve 1byte por vez)
- Endereçamento: por byte (cada endereço aponta pra 1 byte)
  - Exemplo de uma operação:
  - A = A + B (8 bits + 8 bits)

## Registradores

- Registradores Principais (8 bits)
  - `A` – Acumulador
  - `B, C, D, E, H, L` – Registradores de uso geral
- Registradores de 16 bits (pares)
  - `AF` – Acumulador e flags
  - `BC, DE, HL` – Pares de registradores
- Registradores Especiais
  - `PC` (Program Counter) – Contador de programa
  - `SP` (Stack Pointer) – Ponteiro da pilha
  - `IX, IY` – Registradores de índice
- Flags registrador `F` que pode assumir os valores:
  - `S` (sign) -> se 1 resultado negativo
  - `Z` (zero) -> se 1 resultado igual a zero
  - `H` (half carry) -> se 1 houve carry entre nibbles (4 bits)
  - `P/V` (parity/overflow) -> se 1 indica paridade par ou overflow
    - quando ocorre um add (aritmetica), se comporta como overflow
    - quando ocorre uma operacao logica como um and, se comporta como paridade (usado pra identificar erros, se usou um )
  - `N` (add/subtract) -> se 1 a última operação foi subtração
  - `C` (carry) -> se 1 houve vai-um, empréstimo (borrow)

## Modos de endereçamento

- Imediato: tipo ldi do neander operando na instrucao:
  - `LD A, 20` -> `A=20`
- Direto: endereço explicito:
  - `LD A, (1234)` -> `A = memória[1234]`
- Indireto via registrador (HL, IX, IY), registrador guarda o endereço:
  - `LD A, (HL)` -> `A = memória[HL]`
- Indexado (IX + deslocamento, IY + deslocamento), registrador + offset:
  - `LD A, (IX+5)` -> `A = memória[IX + 5]`
- Implícito, operando já definido (instrucao sabe o que usar/fazer)
  - `INC A` -> `A = A + 1`

## Instruções a serem suportadas

; vai ser linha comentada

| Categoria | Instrução    | Descrição curta                  |
| --------- | ------------ | -------------------------------- |
| Dados     | `LD r, r'`   | copia registrador -> registrador |
|           | `LD r, n`    | imediato -> registrador          |
|           | `LD (HL), r` | registrador -> memória[HL]       |
|           | `LD r, (HL)` | memória[HL] -> registrador       |
| Aritm.    | `ADD A, r`   | A = A + r                        |
|           | `SUB r`      | A = A - r                        |
|           | `INC r`      | r = r + 1                        |
|           | `DEC r`      | r = r - 1                        |
|           | `CP r`       | compara A com r (flags)          |
| Lógicas   | `AND r`      | A = A & r                        |
|           | `OR r`       | A = A \| r                       |
|           | `XOR r`      | A = A ^ r                        |
| Fluxo     | `JP addr`    | PC = addr                        |
|           | `JR offset`  | PC += deslocamento               |
|           | `CALL addr`  | chama subrotina                  |
|           | `RET`        | retorna da subrotina             |
| Pilha     | `PUSH rp`    | empilha registrador par          |
|           | `POP rp`     | desempilha registrador par       |
| Exec      | `NOP`        | não faz nada                     |
|           | `HALT`       | para execução                    |

## Pilha da VM

- Controlada pelo registrador SP;
- Cresce de endereços maiores para menores;
  - POP = SP - 1 (ultimo endereço na pilha - 1)
- Armazena endereços de retorno e valores temporários;
- Precisa de tratamento para stack overflow e stack underflow.

## Fluxo teoria:

- 1. entrada: mnemonicos (ADD A, B) ...
- 2. VM interpreta e executa isso (le a entrada, armazena de forma estruturada e começa a executar as operações com os registradores e mudar as flags a cada operação)
  - **Montador**: quem faz o processo de ler mnemonico e transformar em binario. (nesse trabalho é só VM)
  - **VM executor**: while(true) até executar todas instruções (lembra que tem jumps e etc...)
  - **Estado da máquina**: registradores, program counter, SP stack, flags (zero, sign, overflow/paridade), memoria (codigo, dados e stack)
    - **memoria total: 2^16 (nao conta registradores)**
      -- stack comeca no topo, código fica no 0000, dados acima do codigo, stack comeca em tudo 1
      0x0000 ──── início
      [ código ] -> no 0 ta o codigo
      [ dados ] -> dps dados
      [ ... ]
      [ stack ] -> começa no topo e vai indo pra baixo (CUIDADO STACK OVERFLOW)
      0xFFFF ──── fim
  - mem[65536] -> tudo (código + dados + pilha)
  - registradores -> só controle/execução
  - stack -> parte da memória (controlada por SP)

## Fluxo simplificado código:

-- esse seria antes da vm mas ainda nao

- **0 Assembler (ainda nao nessa etapa)**: le mnemonico e gera .bin arquivo com opcode seguindo
  exemplo: [opcode][operand1][operand2]
  ADD A, B -> (assembler) -> 00000001 00000000 00000001

-- esses sim na VM:

- **1o Loader** -> carrega .bin na memória
- **2o VM loop**:

- **Fetch** -> le instrução da memória (0s e 1s com opcode e etc) -> **while na VM mesmo**
  - usa PC program counter pra isso
- **Decoder** -> interpreta bytes (interpreta o que foi lido e transforma em algo estruturado)
  - cria Instruction (em RAM temporária/registrador de instrução)
  - algo tipo `struct Instruction { opcode, operand1, operand2 };` em c++ mesmo normal, nao na vm
- **Executor** -> executa instrução (executa aquilo que ja ta estruturado pelo decoder)
  - **chama CPU** para executar operações (ADD, SUB, MOV)
  - CPU atualiza registradores e flags
