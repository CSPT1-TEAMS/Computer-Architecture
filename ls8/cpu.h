#ifndef _CPU_H_
#define _CPU_H_

#define MAX_ADDR 0xff
#define CPU_FLAG 0x00

// Holds all information about the CPU
typedef struct cpu {
  int flag;
  unsigned char pc;
  unsigned reg[8];
  unsigned ram[MAX_ADDR +1];
} CPU;

// ALU operations
enum alu_op {
	ALU_MUL
	// Add more here
};

// Instructions

// These use binary literals. If these aren't available with your compiler, hex
// literals should be used.

#define LDI  0b10000010
// TODO: more instructions here. These can be used in cpu_run().

// Function declarations

extern void cpu_load(struct cpu *cpu);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
