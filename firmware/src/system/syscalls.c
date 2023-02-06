#include <stdint.h>
#include <sys/stat.h>
#include <errno.h>
#include <system.h>

extern char __heap_start__[];
extern char __heap_end__[];

void _exit(int32_t Status)
{
    while (1);
}
void *_sbrk(int32_t Incr)
{
    static char *spHeapEnd = __heap_start__;
    char *pBase = spHeapEnd;
    if(spHeapEnd + Incr > __heap_end__)
    {
        errno = ENOMEM;
        return (void *)-1;
    }
    spHeapEnd += Incr;
    return pBase;
}

int32_t _isatty(int32_t FD)
{
    return 1;
}

int32_t _fstat(int32_t FD, struct stat *pSt)
{
    pSt->st_mode = S_IFCHR;
    return 0;
}

int32_t _read(int32_t FD, char *pBuff, int32_t Len)
{
    int32_t Ret = 0;
    if(0 == Len)
    {
        return 0;
    }
    return Ret;
}

int32_t _write(int32_t fd, char *pBuff, uint32_t Len)
{
    int32_t Ret = 0;

    if(0 == Len)
    {
        return 0;
    }

    ConsoleWrite((uint8_t *)pBuff, Len);

    return Ret;
}

off_t _lseek(int32_t FD, off_t Offset, int32_t Dir)
{
    return 0;
}

int32_t _close(int32_t FD)
{
    return -1;
}

/* Bare metal, no processes, so always process id 1 */
int32_t _getpid(void)
{
    return 1;
}

/* Bare metal, no processes, so error */
int32_t _kill(int32_t Pid, int32_t Sig)
{
    return -1;
}
