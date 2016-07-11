#include "print.h"

int main(void)
{
    // Printf Test

    clear_screen();
    for(int i=0;i<25;i++)
        print_xy_pm(i,i+28,'x',0x1f);
    for(int i=13;i<25;i++)
        print_xy_pm(i,52-i,'x',0x1f);
    set_cursor(0);
    printf("%s\n","printf(\"printftest %d %d %s %u %x %c %%\",10,-10,\"haha\",-10,10,'c')");
    printf("printftest %d %d %s %u %x %c %%",10,-10,"haha",-10,10,'c');
    while(1) ;
    return 0;
}
