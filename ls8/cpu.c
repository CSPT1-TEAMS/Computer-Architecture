#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char mar)
{
  return cpu->ram[mar];
}

void cpu_ram_write(struct cpu *cpu, unsigned char mar, unsigned char mdr)
{
  cpu->ram[mar] = mdr;
}

void cpu_load(char *filename, struct cpu *cpu)
{

  FILE *fp;
  int address = 0;
  char line[1024];

  // open file
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("INVALID FILE NAME");
    return;
  }

  while (address < 256 && fgets(line, sizeof line, fp) != NULL) //not at eof
  {
    char *end_of_instr;
    unsigned char *data;
    // in a line, save the numeric data (byte/instruction/register/value) in data, ignoring non numeric characters
    data = strtol(line, &end_of_instr, 2);

    // if data != 0, save
    //data can be 0 IF no byte data OR byte = 0
    if (data != end_of_instr) //use pointer to first non-numeric character
    {
      //only write instructions, not comments
      cpu->ram[address] = data;
      address++;
    }
    // else ignore
  }
  fclose(fp);
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op)
  {
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
  int running = 1; // True until we get a HLT instruction or default case

  while (running)
  {
    unsigned char IR = cpu->ram[cpu->PC];
    unsigned char operandA = cpu->ram[cpu->PC + 1];
    unsigned char operandB = cpu->ram[cpu->PC + 2];

    switch (IR)
    {
    case LDI:
      cpu->registers[operandA] = operandB;
      cpu->PC += 3;
      break;
    case HLT:
      running = 0;
      cpu->PC += 1;
      break;
    case PRN:
      printf("%d\n", cpu->registers[operandA]);
      cpu->PC += 2;
      break;
    case MUL:
      cpu->registers[operandA] *= cpu->registers[operandB];
      cpu->PC += 3;
      break; 
    case PUSH:
      //cpu->ram[address] = data;
      cpu->registers[SP]--;
      cpu->ram[cpu->registers[SP]] = cpu->registers[operandA];
      cpu->PC += 2;
      break;
    case POP:
      cpu->registers[operandA] = cpu->ram[cpu->registers[SP]];
      cpu->registers[SP]++;
      cpu->PC += 2;
      // return cpu->registers[operandA]; 
      break;
    default:
      running = 0;
      printf("%s\n", "ERROR");
    }
  }
}

void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->PC = 0;
  memset(cpu->ram, 0, sizeof cpu->ram);             //8
  memset(cpu->registers, 0, sizeof cpu->registers); //256
  // TODO: Zero registers and RAM
  cpu->registers[SP]= ADDR_EMPTY_STACK; //244
}
