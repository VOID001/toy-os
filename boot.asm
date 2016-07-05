mov ah, 0x0e

mov bx, string

loop:
	mov al, [bx]
	cmp al, 0
	je exit
	int 0x10
	inc bx

exit:
	jmp $

string:
	db "Hello world", 0
