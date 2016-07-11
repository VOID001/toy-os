#ifndef _VARARG_H_HEADER
#define _VARARG_H_HEADER

typedef char* va_list;
#define __va_rounded_size(TYPE)  \
    (((sizeof(TYPE)+sizeof(int)-1)/sizeof(int))*sizeof(int))
#define va_start(AP,LASTARG)   \
    (AP=((char*)&(LASTARG)+__va_rounded_size(LASTARG)))
#define va_arg(AP,TYPE) \
  (AP += __va_rounded_size(TYPE), \
       *((TYPE *)(AP-__va_rounded_size(TYPE))))
#endif
