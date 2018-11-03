#include "cpu.h"

#define DATA_LEN 6

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char address)
{
  return cpu->ram[address];
}

void cpu_ram_write(struct cpu *cpu, unsigned char address, unsigned char value)
{
  cpu->ram[address] = value;
}
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
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    unsigned char IR = cpu_ram_read(cpu. cpu->pc);
    unsigned char operandA = cpu_ram_read(cpu, (cpu->pc +1)& MAX_ADDR);
    unsigned char operandB = cpu_ram_read(cpu, (cpu->pc + 2)& MAX_ADDR);

    switch(IR) {
      case PRN:
        printf("%d\n", cpu->reg[operandA]);
        break;

      case LDI:   // LDI/load instruction
        cpu->reg[operandA] = operandB;
        break;

      case HLT: // halt method
        running = 0;
        break;

      case MUL:
        alu(cpu, ALU_MUL, operandA, operandB);
        break;

      case ADD:
        alu(cpu, ALU_ADD, operandA, operandB);
        break;

      case PUSH:  // add push function
        cpu_push(cpu, cpu->reg[operandA]);
        break;

      case POP:
        cpu->reg[operandA] = cpu_pop(cpu);
        break;

      case PRA:
        printf("%c\n", cpu->reg[operandA]);
        break;

      case CALL:  // Call;
        cpu_push(cpu, cpu->pc + 2);
        cpu->pc = cpu->reg[operandA];
        break;

      case RET:
        cpu->pc = cpu_pop(cpu);
        break;

      case CMP:
        if (cpu->reg[operandA] == cpu->reg[operandB])
        {
          cpu->fl = 1;
        } else
        {
          cpu->fl = 0;
        }
        break;

      case JMP:
        cpu->pc = cpu->reg[operandA];
        break;

      case JEQ:
        if (cpu->fl)
        {
          cpu->pc = cpu->reg[operandA];
        }
        else
        {
          cpu->pc += 2;
        }
        break;

      case JNE:
        if (!cpu->fl)
        {
          cpu->pc = cpu->reg[operandA];
        }
        else
        {
          cpu->pc += 2;
        }
        break;

      default:
        printf("Unknown instruction at %02x: %02x\n", cpu->pc, IR);
        exit(2);
    }
    int instruction_set_pc = (IR >> 4) & 1;

    if (!instruction_set_pc)
    {
      cpu->pc += ((IR >> 6) & 0x3) + 1;
    }
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  cpu->pc = START_OF_PROGRAM_ADDR;
  cpu->flag CPU_FLAG;

  cpu->reg[SP] = START_OF_STACK_ADDR;
  cpu->reg[IM] = INTERRUPT_MASK;
  cpu->reg[IS] = INTERRUPTS;

  // TODO: Zero registers and RAM
  memset(cpu->reg, 0, sizeof cpu-reg);
  memset(cpu->ram, 0, sizeof cpu->ram);
}
