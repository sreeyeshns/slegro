#include <errno.h>
#define NULL ((void *)0)

extern char __heap_start__;
extern char __heap_end__;

void _exit(int status)
{
    while (1);
}
void *_sbrk(int incr)
{
    static char *heap_end = &__heap_start__;
    char *base = heap_end;
    if(heap_end + incr > &__heap_end__)
    {
        errno = ENOMEM;
        return (void *)-1;
    }
    heap_end += incr;
    return base;
}
