#ifndef GPU_H
#define GPU_H

#include <stddef.h>

unsigned int gpu_mem_alloc(size_t nbytes, size_t align, unsigned int flags);
unsigned int gpu_mem_free(unsigned int handle);
void *gpu_mem_lock(unsigned int handle);
unsigned int gpu_mem_unlock(unsigned int handle);

unsigned int gpu_execute_code(unsigned int code, unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3, unsigned int r4, unsigned int r5);

unsigned int gpu_get_serial_num(void);

#endif
