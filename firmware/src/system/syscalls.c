#include <stdint.h>
#include <sys/stat.h>
#include <errno.h>
#include <system.h>

extern char __heap_start__[];
extern char __heap_end__[];

void _exit(int32_t status)
{
    while (1);
}
void *_sbrk(int32_t incr)
{
    static char *heap_end = __heap_start__;
    char *base = heap_end;
    if(heap_end + incr > __heap_end__)
    {
        errno = ENOMEM;
        return (void *)-1;
    }
    heap_end += incr;
    return base;
}

int32_t _isatty(int32_t fd)
{
    return 1;
}

int32_t _fstat(int32_t fd, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int32_t _read(int32_t fd, char *ptr, int32_t len)
{
    int32_t ret = 0;
    if(0 == len)
    {
        return 0;
    }
    return ret;
}

int32_t _write(int32_t fd, char *ptr, uint32_t len)
{
    int32_t ret = 0;

    if(0 == len)
    {
        return 0;
    }

    console_write((uint8_t *)ptr, len);

    return ret;
}

off_t _lseek(int32_t fd, off_t offset, int32_t dir)
{
    return 0;
}

int32_t _close(int32_t fd)
{
    return -1;
}

/* Bare metal, no processes, so always process id 1 */
int32_t _getpid(void)
{
    return 1;
}

/* Bare metal, no processes, so error */
int32_t _kill(int32_t pid, int32_t sig)
{
    return -1;
}
