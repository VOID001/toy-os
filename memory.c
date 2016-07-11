#include "memory.h"
#include "type.h"

void memcpy(void *dst, void *src, uint count)
{
    char *cdst = (char *)dst;
    char *csrc = (char *)src;
    
    for(uint i = 0; i < count; i++)
        *(cdst + i) = *(csrc + i);
}
