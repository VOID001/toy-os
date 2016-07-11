/* Interrupt Descriptor Table and IDT descriptor */
#ifndef _IDT_H_HEADER
#define _IDT_H_HEADER

#include "type.h"

#define TYPE_INTGATE 0x8E

typedef struct idtr {
    ushort limit;
    uint base;
}__attribute__((packed)) IDTdesc;

typedef struct gatedesc {
    ushort offset0_15;
    ushort select;
    uchar zero;
    uchar type_attr;
    ushort offset16_31;
}__attribute__((packed)) Gatedesc;

void init_idt(void);
void set_gatedesc(Gatedesc *entry, uint offset, ushort select, uchar type_attr);

extern void handler_int21(void);
extern void handler_int28(void);
extern void handler_stub(void);

#endif
