#ifndef _CPU_H_
#define _CPU_H_

// Holds all information about the CPU
struct cpu {
  // TODO
  // PC
  unsigned char PC; 
  // registers (array)
  unsigned char registers[8];
  // ram (array)
  unsigned char ram[256];
};

// ALU operations
enum alu_op {
	ALU_MUL
	// Add more here
};

// Instructions

// These use binary literals. If these aren't available with your compiler, hex
// literals should be used.

#define LDI  0b10000010
#define HLT  0b00000001
#define PRN  0b01000111
#define MUL  0b10100010
#define CALL 0b01010000
#define ADD  0b10100000
#define PRA  0b01001000
#define IREG 0b00010011
#define INC  0b01100101
#define JMP  0b01010100
#define PUSH 0b01000101
#define POP  0b01000110
#define DEC  0b01100110
// TODO: more instructions here. These can be used in cpu_run().
#define ADDR_PROGRAM_ENTRY 0x00
#define ADDR_EMPTY_STACK 0xF4
#define SP 7
// Function declarations

extern void cpu_load(char *filename, struct cpu *cpu);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
