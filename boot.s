# A simple boot demo just to print a string when booting the PC

.file  "boot.s"
.code16
.globl _start

.text

_start:

	mov $0x0e, %ah

	mov $string, %bx # We must add a '$' before the label, to specify we want JUST the label addr not the content in this addr

# A loop to print the string
loop:
	mov (%bx), %al
	cmp $0x00, %al
	je  exit
	add $0x01, %bx
	int $0x10
	jmp loop

exit:
	jmp exit

string:
	.string "Hello Niconico"

