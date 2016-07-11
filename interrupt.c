#include "interrupt.h"

void handler_int21(void)
{
    //print_xy_pm(10, 20, 'X', 0x1c);
    while(1);
    asm volatile ("iret" : :);
}

void handler_int28(void)
{
    while(1);
}

void handler_stub(void)
{
    //print_xy_pm(10, 20, 'X', 0x1c);
    while(1);
    asm volatile ("iret" : :);
}

void init_pic(void)
{
    // Block all interrupts
    outb(PIC0_IMR, 0xFF);
    outb(PIC1_IMR, 0xFF);

    outb(PIC0_ICW1, 0x11);
    outb(PIC0_ICW2, 0x20);
    outb(PIC0_ICW3, IRQ_SLAVE);
    outb(PIC0_ICW4, 0x01);

    outb(PIC1_ICW1, 0x11);
    outb(PIC1_ICW2, 0x28);
    outb(PIC1_ICW3, IRQ_SLAVE);
    outb(PIC1_ICW4, 0x01);
    
    outb(PIC0_IMR, 0);
    outb(PIC1_IMR, 0);

}
