OBJCOPY=objcopy
AS=as
QEMU=qemu-system-i386
LD=ld

# target boot and boot-dbg is for make a raw bootable binary image
#

.PHONY: boot boot-dbg clean

boot: boot.s
	$(AS) -o boot.o boot.s
	$(LD) -Ttext 0x7c00 -o boot.bin boot.o
	$(OBJCOPY) -O binary boot.bin
	./sign.pl boot.bin
	$(QEMU) boot.bin

boot-dbg: boot.s
	$(AS) -o boot.o boot.s
	$(LD) -Ttext 0x7c00 -o boot.bin boot.o
	$(OBJCOPY) -O binary boot.bin
	./sign.pl boot.bin
	$(QEMU) -s -S boot.bin

clean:
	- rm *.bin *.o


	


	
