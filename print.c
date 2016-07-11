#include "print.h"

int get_offset(int x,int y)
{
    return 2*(x*MAX_COLS + y);
}

int get_cursor()
{
    outb(SCREEN_CTRL,14);
    int offset=inb(SCREEN_DATA)<<8;
    outb(SCREEN_CTRL,15);
    offset+=inb(SCREEN_DATA);
    return offset*2;
}

void set_cursor(int offset)
{
    offset/=2;
    outb(SCREEN_CTRL,14);
    outb(SCREEN_DATA,(uchar)(offset>>8));
    outb(SCREEN_CTRL,15);
    outb(SCREEN_DATA,(uchar)(offset&0xff));
}

int handle_scroll(int offset)
{
    if(offset<MAX_ROWS*MAX_COLS*2)    return offset;
    for(int i=1;i<MAX_ROWS;i++)
        memcpy((char*)get_offset(i-1,0)+VIDEO_ADDR,(char*)get_offset(i,0)+VIDEO_ADDR,MAX_COLS*2);
    char *lastline = (char*)get_offset(MAX_ROWS-1,0)+VIDEO_ADDR;
    for(int i=0;i<MAX_COLS*2;i++)
        lastline[i]=0;
    offset-=2*MAX_COLS;
    return offset;
}

void print_xy_pm(int x,int y,char xc,char theme)
{
    if(!theme)    theme = DEF_SCHEME;
    int offset;
    if(x>=0 && y>=0)    offset=get_offset(x,y);
    else    offset=get_cursor();
    char *video = (char*)VIDEO_ADDR;
    if(xc=='\n')
    {
        int rows=offset/(2*MAX_COLS);
        offset=get_offset(rows,79);
    }
    else
    {   video[offset] = xc;
        video[offset+1] = theme;
    }
    offset+=2;
    offset=handle_scroll(offset);
    set_cursor(offset);
}


void print_string_pm(int x,int y,char *str,char theme)
{
    if(x>=0&&y>=0)    
        set_cursor(get_offset(x,y));
    for(int i=0; str[i]; i++)
        print_xy_pm(-1,-1,str[i],theme); //since we already set the cursor,we can safely let the print_xy_pm locate the cursor for us;
}

void print_string(char *str)
{
    print_string_pm(-1,-1,str,DEF_SCHEME);
}

void clear_screen()
{
    for(int i=0;i<MAX_ROWS;i++)
        for(int j=0;j<MAX_COLS;j++)
            print_xy_pm(i,j,' ',DEF_SCHEME);
    set_cursor(0);
}

void printint(int num,int base,int sign)
{
    static char digits[] = "0123456789abcdef";
    char buf[16];
    uint n=num;
    if(sign&&num<0)
    {
        n=-num;
        print_xy_pm(-1,-1,'-',DEF_SCHEME);
    }
    if(base==16)
        print_string("0x");
    if(n==0)
    {
        print_xy_pm(-1,-1,'0',DEF_SCHEME);
        return;
    }
    int cur=0;
    while(n)
    {
        buf[cur++]=digits[n%base];
        n/=base;
    }
    for(int i=cur-1;i>=0;i--)
        print_xy_pm(-1,-1,buf[i],DEF_SCHEME);
}

void printf(char *fmt,...)
{
    va_list ap;
    va_start(ap,fmt);
    char c,*s;
    while(*fmt)
    {
        c=*fmt++;
        if(c!='%')
        {
            print_xy_pm(-1,-1,c,DEF_SCHEME);
            continue;
        }
        c=*fmt++;
        if(c==0)    break;
        switch(c)
        {
            case 'd':
                printint(va_arg(ap,int),10,1);
                break;
            case 'u':
                printint(va_arg(ap,uint),10,0);
                break;
            case 'x':
                printint(va_arg(ap,int),16,0);
                break;
            case 's':
                s=va_arg(ap,char*);
                while(*s)
                    print_xy_pm(-1,-1,*s++,DEF_SCHEME);
                break;
            case 'c':
                print_xy_pm(-1,-1,va_arg(ap,char),DEF_SCHEME);
                break;
            case '%':
                print_xy_pm(-1,-1,'%',DEF_SCHEME);
        }
    }
}
