OBJS = kernel.o \
	   memory.o \
	   print.o \
	   interrupt.o \
	   idt.o \


OBJCOPY=objcopy
AS=as
QEMU=qemu-system-i386
LD=ld
CFLAGS = -fno-pic -static -fno-builtin -fno-strict-aliasing -fvar-tracking -fvar-tracking-assignments -O0 -g -Wall -MD -gdwarf-2 -m32 -Werror -fno-omit-frame-pointer
#CFLAGS = -m32 -fno-builtin -g
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)
LDFLAGS += -m $(shell $(LD) -V | grep elf_i386 2>/dev/null)
ASFLAGS += --32

CRTI_OBJ=$(shell $(CC) $(CFLAGS) -print-file-name=crti.o)
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ=$(shell $(CC) $(CFLAGS) -print-file-name=crtn.o)

OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)

STRIP = strip



# target boot and boot-dbg is for make a raw bootable binary image
#

.PHONY: boot boot-dbg clean

boot.o: boot.c
	- $(CC) $(CFLAGS) -O -Os -fno-pic -nostdinc boot.c -c

boot_asm.o: boot.s
	- $(AS) $(ASFLAGS) -o boot_asm.o boot.s

.o: .c
	- $(CC) $(CFLAGS) -c $<


boot.bin: boot.o boot_asm.o
	- $(LD) $(LDFLAGS) -Ttext 0x7c00 -o boot.bin boot_asm.o boot.o
	- $(STRIP) boot.bin
	- $(OBJCOPY) -O binary boot.bin
	- ./sign.pl boot.bin

boot: toy-os.img
	- $(QEMU) toy-os.img -m 1000

boot-dbg: toy-os.img
	- $(QEMU) -s -S toy-os.img -m 1000

kernel.bin: $(OBJS)
	- $(LD) $(LDFLAGS) -T kernel.ld -o kernel.out $(OBJS)
	- $(OBJCOPY) -Obinary kernel.out kernel.bin

toy-os.img: kernel.bin boot.bin 
	- cat boot.bin kernel.bin > toy-os.img

clean:
	- rm *.bin *.o *.out
