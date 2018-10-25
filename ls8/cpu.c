#include "cpu.h"

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
    // From print8.ls8
    0b10000010, // LDI R0,8
    0b00000000,
    0b00001000,
    0b01000111, // PRN R0
    0b00000000,
    0b00000001  // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */

//  This is the workhorse function of the entire processor. It's the most difficult
// part to write.

// It needs to read the memory address that's stored in register `PC`, and store
// that result in `IR`, the _Instruction Register_. This can just be a local
// variable in `cpu_run()`.

// Some instructions requires up to the next two bytes of data _after_ the `PC` in
// memory to perform operations on. Sometimes the byte value is a register number,
// other times it's a constant value (in the case of `LDI`). Using
// `cpu_ram_read()`, read the bytes at `PC+1` and `PC+2` from RAM into variables
// `operandA` and `operandB` in case the instruction needs them.

// Then, depending on the value of the opcode, perform the actions needed for the
// instruction per the LS-8 spec. Maybe a `switch` statement...? Plenty of options.

// After the handler returns, the `PC` needs to be updated to point to the next
// instruction for the next iteration of the loop in `cpu_run()`. The number of
// bytes an instruction uses can be determined from the two high bits (bits 6-7) of
// the instruction opcode. See the LS-8 spec for details.
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // 2. switch() over it to decide on a course of action.
    // 3. Do whatever the instruction should do according to the spec.
    // 4. Move the PC to the next instruction.

    unsigned char IR;
    unsigned char operandA = cpu_ram_read(cpu, cpu->PC + 1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->PC + 2);
  }
}

/**
 * Initialize a CPU struct
 */

unsigned char cpu_ram_read( struct cpu *cpu, unsigned char mar)  
{
  return cpu->ram[mar];
}

void cpu_ram_write( struct cpu *cpu, unsigned char mar, unsigned char mdr )
{
  cpu->ram[mar] = mdr;
}

void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->PC = 0;
  memset(cpu->registers, 0, sizeof(int)*8);
  memset(cpu->ram, 0, sizeof(int)*256);
  // TODO: Zero registers and RAM

  //   The `cpu_init()` function takes a pointer to a `struct cpu` and initializes it
  // as necessary. At first, the PC, registers, and RAM should be cleared to zero.
  // (`memset()` might help you clear registers and RAM.)

  // Later on, you might do further initialization here, e.g. setting the initial
  // value of the stack pointer.
}
