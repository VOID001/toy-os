#ifndef _PRINT_H_HEADER
#define _PRINT_H_HEADER

#define VIDEO_ADDR  0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define DEF_SCHEME 0x0f

#define SCREEN_CTRL 0x3d4
#define SCREEN_DATA 0X3d5

#include "c_x86asm.h"
#include "memory.h"
#include "vararg.h"

int get_offset(int x,int y);
int get_cursor();
void set_cursor(int offset);
int handle_scroll(int offset);
void print_xy_pm(int x,int y,char xc,char theme);
void print_string_pm(int x,int y,char *str,char theme);
void print_string(char *str);
void clear_screen();
void printint(int num,int base,int sign);
void printf(char *fmt,...);

#endif
