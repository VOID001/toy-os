#ifndef _INTERRUPT_H_HEADER
#define _INTERRUPT_H_HEADER

#include "c_x86asm.h"
#include "type.h"
#include "print.h"
#include "idt.h"
 
/* Define PIC Port and Masks */
 
#define PIC0_ICW1   0x20        // Master PIC (IRQ 0-7)
#define PIC1_ICW1   0xA0        // Slave PIC(IRQ 8-15)
 
#define PIC0_IMR    0x21
#define PIC1_IMR    0xA1
 
#define PIC0_ICW2   0x21
#define PIC1_ICW2   0xA1
#define PIC0_ICW3   0x21
#define PIC1_ICW3   0xA1
#define PIC0_ICW4   0x21
#define PIC1_ICW4   0xA1
 
#define IRQ_SLAVE 2

void init_pic(void);
void handle_int21(void);

#endif

