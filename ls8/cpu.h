#ifndef _CPU_H_
#define _CPU_H_

#define MAX_ADDR 0xff
#define CPU_FLAG 0x00

#define SP 7
#define IS 6
#define IM 5

#define START_OF_STACK_ADDR 0xf4
#define START_OF_PROGRAM_ADDR 0x00
#define INTERRUPT_MASK 0X00
#define INTERRUPTS 0X00

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

#define LDI 0b10000010
#define PRN 0b01000111
#define HLT 0b00000001
#define PRA 0b01001000
#define POP 0b01000110
#define PUSH 0b01000101
#define ADD  0b10100000
#define MUL  0b10100010
#define CALL 0b01010000
#define RET  0b00010001
#define CMP  0b10100111
#define INT  0b01010010
#define JEQ  0b01010101
#define JNE  0b01010110
#define JMP  0b01010100
// TODO: more instructions here. These can be used in cpu_run().

// Function declarations

extern void cpu_load(struct cpu *cpu);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
