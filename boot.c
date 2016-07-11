#include "type.h"
#include "c_x86asm.h"

#define SECTOR_SIZE 512
#define OS_START_AT 0x200000

void readseg(uchar*, uint, uint);
void waitdisk();

void bootmain(void)
{
    int (*entry)(void);
    uchar *dst = (uchar *)OS_START_AT;
    // Load the kernel into memory

    readseg(dst, 4096, 0);

    // Call entry point
    entry = (int(*) (void))OS_START_AT;
    entry();
    return ;
}

// Read a single sector to memory given by dist
// sector provided by sector_id
void readsect(void *dst, uint sector_id)
{
    waitdisk();
    outb(0x1F2, 1);
    outb(0x1F3, sector_id);
    outb(0x1F4, sector_id >> 8);
    outb(0x1F5, sector_id >> 16);
    outb(0x1F6, (sector_id >> 24) | 0xE0);
    outb(0x1F7, 0x20); // read sectors, command 0x20

    waitdisk();
    insl(0x1F0, dst, SECTOR_SIZE / 4);
}

void waitdisk()
{
    // loop until the disk is ready
    while((inb(0x1F7) & 0xC0) != 0x40)
        ;
}

// Read count bytes from kernel at offset, maybe read more than expected
// store the result into memory started at dst
// May read more than expected
void readseg(uchar *dst, uint count, uint offset)
{
    uchar *edst = dst + count;

    // round dst down to sector boundary
    dst -= offset % SECTOR_SIZE;

    // kernel start at sector 1
    offset = (offset / SECTOR_SIZE) + 1;

    for(; dst < edst; dst += SECTOR_SIZE, offset++)
        readsect(dst, offset);
}
