# A simple boot demo just to print a string when booting the PC

.file "boot.s"

	CODE_SEG = gdt_code - gdt_start
	DATA_SEG = gdt_data - gdt_start
	VIDEO_MEM = 0xb8000
	THEME = 0x1c

	.text
	.globl _start
	.code16

_start:

	mov $0x0e, %ah

	mov $string, %bx # We must add a '$' before the label, to specify we want JUST the label addr not the content in this addr

# A loop to print the string
loop:
	mov (%bx), %al
	cmp $0x00, %al
	je  to32
	add $0x01, %bx
	int $0x10
	jmp loop

to32:
	cli
	lgdt gdt_descriptor
	mov  %cr0, %eax
	or   $0x1, %eax
	mov  %eax, %cr0

	ljmp $0x8, $init_pm

# Construct the GDT

gdt_start:

gdt_null:
	.long 0x0
	.long 0x0

gdt_code:
	.word 0xffff
	.word 0x0
	.byte 0x0
	.byte 0b10011010
	.byte 0b11001111
	.byte 0x0

gdt_data:
	.word 0xffff
	.word 0x0
	.byte 0x0
	.byte 0b10010010
	.byte 0b11001111
	.byte 0x0

gdt_end:

# Construct the GDT Descriptor
.zero 16

gdt_descriptor:
	.word gdt_end - gdt_start - 1
	.long gdt_start
	.zero 16

string:
	.string "Booting The Toy-OS"

	.code32

init_pm:

	mov $DATA_SEG, %ax
	mov %ax, %ds
	mov %ax, %ss
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %es

# Try to print a character on screen

mov $VIDEO_MEM, %edx

print_char_pm:
	mov $'@', %al
	mov $THEME, %ah
	mov %ax, (%edx)
	add $2, %edx
	jmp print_char_pm

looop:
	jmp looop
