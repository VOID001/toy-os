/* X86 Assemble Instructions wrapper in C */
#ifndef _C_X86ASM_H_HEADER
#define _C_X86ASM_H_HEADER
#include "type.h"

// Read the data from IO port
static inline uchar inb(ushort port)
{
    uchar data;

    asm volatile ("in %1,%0" : "=a" (data) : "d" (port));
    return data;
}

// Send the data to IO port
static inline void outb(ushort port, uchar data)
{
    asm volatile ("out %0,%1" : /* output regs empty */ :"a" (data), "d" (port));
}

// Read cnt * 4 bytes data from port to memory, specified by addr
static inline void insl(int port, void *addr, int cnt)
{
    asm volatile("cld; rep insl" : 
            "=D" (addr), "=c" (cnt) :
            "d" (port), "0" (addr), "1" (cnt) :
            "memory", "cc");

}

static inline void lidt(uint addr)
{
    asm volatile("lidt (%0)" : : "r" (addr));
}

static inline void sti(void)
{
    asm volatile("sti" : :);
}

#endif
