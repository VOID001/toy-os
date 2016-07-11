#include "idt.h"
#include "c_x86asm.h"
#include "print.h"

Gatedesc idt[256];
IDTdesc idtdesc;
int deadbeef = 0xdeadbeef;

void init_idt(void)
{

    //Init idtdesc first
    idtdesc.base = (uint)idt;         // Base addr
    idtdesc.limit = 0xFF;       // 256 entries

    printf("\nThe idt address is %x\n", idt);
    printf("\nThe deadbeef address is %x\n", &deadbeef);
    printf("The handler_stub address is %x\n", handler_stub);
    printf("The handler_int21 address is %x\n", handler_int21);
    printf("The handler_int28 address is %x\n", handler_int28);

    for(int i = 0; i < 256; i++)
    {
        set_gatedesc(idt + i, (uint)handler_stub, 0x08, 0);
    }

    // Set the intterupt for Keyboard
    //
    for(int i = 0x21; i <= 0x2f; i++)
        set_gatedesc(idt + i, (uint)handler_stub, 0x08, TYPE_INTGATE);

    set_gatedesc(idt + 0x21, (uint)handler_int21, 0x08, TYPE_INTGATE);
    set_gatedesc(idt + 0x28, (uint)handler_int28, 0x08, TYPE_INTGATE);

    lidt((uint)&idtdesc);

    return ;
}

void set_gatedesc(Gatedesc *entry, uint offset, ushort select, uchar type_attr)
{
    entry->offset0_15 = offset & 0xFFFF;
    entry->select = select;
    entry->type_attr = type_attr;
    entry->offset16_31 = (offset >> 16) & 0xFFFF;
}
